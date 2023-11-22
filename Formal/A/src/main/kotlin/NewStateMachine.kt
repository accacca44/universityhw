package main.kotlin

import State
import java.io.File
import java.util.LinkedList
import java.util.Queue

class NewStateMachine {
    private val eps = "eps"
    private val pseudoState = "PS"
    private var fileContent = ""
    private var states: MutableMap<String, State> = mutableMapOf()
    private var symbols: ArrayList<String> = ArrayList()
    private var initialLabels: ArrayList<String> = ArrayList()
    private var finalLabels: ArrayList<String> = ArrayList()

    constructor(fileContent: String){
        this.fileContent = fileContent
        val lines = fileContent.lines()

        // check for empty file
        if(lines.isEmpty()){
            println("The input is empty!")
            return
        }

        // read state labels and create state objects
        val stateLabels = lines[0].split(" ")
        for( label in stateLabels) {
            states[label] = State(label)
        }

        // read symbols from file
        val symbolLabels = lines[1].split(" ")
        for(symbol in symbolLabels) {
            symbols.add(symbol)
        }

        // read initial nodes/entry points
        val entryPoints = lines[2].split(" ")
        for (entryPoint in entryPoints){
            states[entryPoint]?.isInitial = true
            initialLabels.add(entryPoint)
        }

        // read final nodes/entry points
        val finalPoints = lines[3].split(" ")
        for (finalPoint in finalPoints){
            states[finalPoint]?.isFinal = true
            finalLabels.add(finalPoint)
        }

        // read connections for each state
        for (i in 4..<lines.size) {
            if (lines[i] != "") {
                val connectionsStrings = lines[i].split(" ")
                val startLabel = connectionsStrings[0]
                val symbolLabel = connectionsStrings[1]
                val endLabel = connectionsStrings[2]

                states[startLabel]?.connections?.set(Pair(symbolLabel, endLabel), endLabel)
            }
        }
    }
    constructor(file: File) : this(file.readText())

    fun generateDotCode(): String {

        // Base template DOT code
        var dotCode = "digraph G{\n" +
                "ranksep =0.5;\n" +
                "nodesep =0.5;\n" +
                "rankdir = LR ;\n" +
                "node [ shape = circle  , fontsize = 16  ];\n" +
                "fontsize = 10 ;\n" +
                "compound = true ;\n" +
                "@INVIS" +
                "@END" +
                "@INVISCON" +
                "@REALCON" +
                "}"

        // Place invisible initial nodes
        var invisibleNodes = ""
        for(node in initialLabels) {
            invisibleNodes += "i$node [shape=point , style=invis];\n"
        }

        // Place final nodes
        var endNodes = ""
        for(node in finalLabels) {
            endNodes += "$node [shape=doublecircle];\n"
        }

        // Place invisible connections
        var invisibleConnections = ""
        for(node in initialLabels) {
            invisibleConnections += "i$node -> $node;\n"
        }

        var realConnections = ""
        for((stateLabel, state) in states) {
            for((keyPair, endStateLabel) in state.connections) {

                // if there is already a transition between two states,
                // just update the current edge, do not create a new one
                val currentEdge = "$stateLabel -> $endStateLabel [label=\""
                if(realConnections.contains(currentEdge)){
                    val updatedEdge = "$stateLabel -> $endStateLabel [label=\"${keyPair.first},"
                    realConnections = realConnections.replaceFirst(currentEdge, updatedEdge)
                } else {
                    realConnections += "$stateLabel -> $endStateLabel [label=\"${keyPair.first}\"];\n"
                }
            }
        }

        dotCode = dotCode.replaceFirst("@INVIS",invisibleNodes)
        dotCode = dotCode.replaceFirst("@END",endNodes)
        dotCode = dotCode.replaceFirst("@INVISCON",invisibleConnections)
        dotCode = dotCode.replaceFirst("@REALCON",realConnections)
        print(dotCode)
        return dotCode
    }

    // Eliminates unreachable states
    fun eliminateUnreachableStates() : NewStateMachine {

        var globallyVisited = mutableSetOf<String>()
        var globallyVisitedEdges = mutableSetOf<String>()

        // Perform a BFS on the automata graph for each entry point
        for(entryPoint in initialLabels) {
            var visitedStates = mutableSetOf<String>()
            var queue = mutableListOf<String>()

            queue.add(entryPoint)
            while(queue.isNotEmpty()) {
                val currentStateLabel = queue.removeAt(0)
                val currentConnections = states[currentStateLabel]?.connections

                if (currentConnections != null) {
                    for((symbol, endStateLabel) in currentConnections.keys) {
                        if(endStateLabel !in visitedStates) {
                            visitedStates.add(endStateLabel)
                            globallyVisited.add(endStateLabel)
                            queue.add(endStateLabel)
                        }
                        if(symbol !in globallyVisitedEdges) {
                            globallyVisitedEdges.add(symbol)
                        }
                    }
                }
            }
        }

        // Create the list of unvisited states
        val unVisitedStates = mutableListOf<String>()
        for(key in states.keys) {
            if(key !in globallyVisited && key !in initialLabels) {
                unVisitedStates.add(key)
            }
        }



        // Create automata grammar for the new system
        val allStates = states.keys.filter { state -> state !in unVisitedStates }.toString().replace("[","").replace("]","").replace(",","") + "\n"
        val allSymbols = globallyVisitedEdges.toString().replace("[","").replace("]","").replace(",","") + "\n"
        val initStates = initialLabels.toString().replace("[","").replace("]","").replace(",","") + "\n"
        val endStates = finalLabels.toString().replace("[","").replace("]","").replace(",","") + "\n"

        // read connections for each state
        var transitions = ""
        val lines = fileContent.lines()
        for (i in 4..<lines.size) {
            if(lines[i] != "") {
                val connectionsStrings = lines[i].split(" ")
                val startLabel = connectionsStrings[0]
                val symbolLabel = connectionsStrings[1]
                val endLabel = connectionsStrings[2]

                if (startLabel !in unVisitedStates && endLabel !in unVisitedStates) {
                    transitions += "${lines[i]}\n"
                }
            }
        }

        val content = allStates + allSymbols + initStates + endStates + transitions
        return NewStateMachine(content.reversed().replaceFirst("\n", "").reversed())
    }

    fun eliminateNonProductiveStates(): NewStateMachine {
        var globallyVisited = mutableSetOf<String>()
        var globallyVisitedEdges = mutableSetOf<String>()

        // Perform a BFS on the automata graph for each end point
        for(endPoint in finalLabels) {
            var visitedStates = mutableSetOf<String>()
            var queue = mutableListOf<String>()

            queue.add(endPoint)
            while(queue.isNotEmpty()) {
                val currentStateLabel = queue.removeAt(0)
                val currentConnections = getPreviousStates(currentStateLabel)

                for((prevStateLabel, symbol) in currentConnections) {
                    if(prevStateLabel !in visitedStates) {
                        visitedStates.add(prevStateLabel)
                        globallyVisited.add(prevStateLabel)
                        queue.add(prevStateLabel)
                    }
                    if(symbol !in globallyVisitedEdges) {
                        globallyVisitedEdges.add(symbol)
                    }
                }
            }
        }

        // Create the list of unvisited states
        val unVisitedStates = mutableListOf<String>()
        for(key in states.keys) {
            if(key !in globallyVisited && key !in finalLabels) {
                unVisitedStates.add(key)
            }
        }

        // Create automata grammar for the new system
        val allStates = states.keys.filter { state -> state !in unVisitedStates }.toString().replace("[","").replace("]","").replace(",","") + "\n"
        val allSymbols = globallyVisitedEdges.toString().replace("[","").replace("]","").replace(",","") + "\n"
        val initStates = initialLabels.toString().replace("[","").replace("]","").replace(",","") + "\n"
        val endStates = finalLabels.toString().replace("[","").replace("]","").replace(",","") + "\n"

        // read connections for each state
        var transitions = ""
        val lines = fileContent.lines()
        for (i in 4..<lines.size) {
            if(lines[i] != "") {
                val connectionsStrings = lines[i].split(" ")
                val startLabel = connectionsStrings[0]
                val symbolLabel = connectionsStrings[1]
                val endLabel = connectionsStrings[2]

                if (startLabel !in unVisitedStates && endLabel !in unVisitedStates) {
                    transitions += "${lines[i]}\n"
                }
            }
        }

        val content = allStates + allSymbols + initStates + endStates + transitions
        return NewStateMachine(content.reversed().replaceFirst("\n","").reversed())
        }

    // TODO - Not generating images
    fun genImage(outputFileName: String) {
        val dotCode = generateDotCode()
        Runtime.getRuntime().exec("echo HEllo WOrlds!")
        val genImgCommand = "echo $dotCode | dot -T png > src/test/out/$outputFileName.png"
        Runtime.getRuntime().exec(genImgCommand)
    }

    // Returns a complete FTA from a DVA
    private fun complete(): NewStateMachine {

        // Create automata grammar for the new system
        var allStates = states.keys.toString().replace("[","").replace("]","").replace(",","") + "\n"
        val allSymbols = symbols.toString().replace("[","").replace("]","").replace(",","") + "\n"
        val initStates = initialLabels.toString().replace("[","").replace("]","").replace(",","") + "\n"
        val endStates = finalLabels.toString().replace("[","").replace("]","").replace(",","") + "\n"

        // read connections for each state
        var transitions = ""
        val lines = fileContent.lines()
        for (i in 4..<lines.size) {
            transitions += "${lines[i]}\n"
        }

        val transitionLines = completeTransitions(transitions, symbols, states.keys)

        // If a pseudo state was needed, then insert the pseudo state to the 'allStates' list
        if(transitionLines.lines().size > transitions.lines().size) {
            allStates = allStates.reversed().replaceFirst("\n", "\n${pseudoState.reversed()} ").reversed()
        }

        val content = allStates + allSymbols + initStates + endStates + transitionLines
        return NewStateMachine(fileContentify(content))
    }

    fun isEquivalent(someSM: NewStateMachine): Boolean {
        // check if ABcs are equal
        val thisSM = this.eliminateUnreachableStates().eliminateNonProductiveStates().complete()
        val otherSM = someSM.eliminateNonProductiveStates().eliminateUnreachableStates().complete()

//        thisSM.generateDotCode()
//        otherSM.generateDotCode()

        if(thisSM.symbols.sorted() != otherSM.symbols.sorted()) {
            // ABCs are not equal
            return false
        }

        // Check if the statePair were visited
        val visited = mutableSetOf<Pair<String, String>>()

        // Verify if only one starting state is present
        if(thisSM.initialLabels.size > 1 || otherSM.initialLabels.size > 1) {
            error("State Machines have more than one entry points!")
        }

        // Verify status of state entry point-node
        val thisInitLab = thisSM.initialLabels[0]
        val otherInitLab = otherSM.initialLabels[0]
        if(thisSM.states[thisInitLab]?.isFinal == true xor (otherSM.states[otherInitLab]?.isFinal == true)){
            // The initial states were different type
            return false
        }

        // For every symbol check all the neighbouring states
        val queue: Queue<Pair<String, String>> = LinkedList()
        var currentPair = Pair(thisInitLab, otherInitLab)
        queue.add(currentPair)
        while(queue.isNotEmpty()) {
            currentPair = queue.remove()

            for (symbol in symbols) {

                // Get the next states
                val thisNextStateLabel = thisSM
                    .states[currentPair.first]
                    ?.connections
                    ?.keys
                    ?.filter { key -> key.first == symbol }
                    ?.get(0)
                    ?.second
                val otherNextStateLabel = otherSM
                    .states[currentPair.first]
                    ?.connections
                    ?.keys
                    ?.filter { key -> key.first == symbol }
                    ?.get(0)
                    ?.second
                val nextPair = Pair(thisNextStateLabel, otherNextStateLabel)

                if(nextPair !in visited) {
                    // Check if next states aren't the same
                    if (thisSM.states[thisNextStateLabel]?.isFinal == true xor (otherSM.states[otherNextStateLabel]?.isFinal == true)) {
                        return false
                    }

                    // Mark states as visited
                    queue.add(nextPair as Pair<String, String>?)
                    visited.add(nextPair)
                }
            }
        }
        return true
    }

    private fun completeTransitions(transitions: String, symbols: ArrayList<String>, states: Collection<String>): String {
        val transitionLines = transitions.lines().sorted()
        // for every state check every symbol, if not exists, create new transitions
        var newTransitions = ""
        for(state in states) {
           for(symbol in symbols) {
               val firstPart = "$state $symbol"
               val pattern = Regex("^$firstPart|\n$firstPart")

               if(pattern.find(transitions) == null) {
                   newTransitions += "$firstPart $pseudoState\n"
               }
           }
        }

        // For the pseudo state,connect all symbols to itself
        if(newTransitions != "") {
            for (symbol in symbols) {
                newTransitions += "$pseudoState $symbol $pseudoState\n"
            }
        }

        return fileContentify("$transitions$newTransitions\n")
    }


    // Minimize the DFA
    fun minimal() {
        val thisSM = this.eliminateUnreachableStates().complete()
        thisSM.generateDotCode()

        val marked = mutableSetOf<Pair<String, String>>()
        val unMarked = mutableSetOf<Pair<String, String>>()
        val lists = mutableMapOf<Pair<String,String>, List<Pair<String,String>>>()

        // Mark every pair of state that have different 'isFinal' values
        for((labelA, stateA) in thisSM.states) {
            for((labelB, stateB) in thisSM.states) {
                if (labelA < labelB) {
                    val newPair = Pair(labelA, labelB)
                    if(stateA.isFinal != stateB.isFinal) {
                        if (newPair !in marked) {
                            marked.add(newPair)
                        } else {
                            unMarked.add(newPair)
                        }
                    }
                }
            }
        }




    }

    private fun getPreviousStates(stateLabel: String): MutableList<Pair<String, String>> {
        val list = mutableListOf<Pair<String,String>>()

        for ((prevState, stateData) in states){
            for(con in stateData.connections.keys){
                if(con.second == stateLabel){
                    list.add(Pair(prevState, con.first))
                }
            }
        }
        return list
    }

    private fun fileContentify(fileContent: String): String {
        return fileContent.reversed().replaceFirst("\n", "").reversed()
    }

}