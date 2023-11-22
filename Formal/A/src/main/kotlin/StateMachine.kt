import java.io.File

class StateMachine {

        private val eps = "eps"
        private var states: MutableMap<String, State> = mutableMapOf()
        private var symbols: ArrayList<String> = ArrayList()
        private var initialLabels: ArrayList<String> = ArrayList()
        private var finalLabels: ArrayList<String> = ArrayList()

        // Read the automate grammar and create the state machine
        private fun loadStates(file: File) {
            loadStates(file.readText())
        }
        fun loadStates(fileContent: String) {
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
                val connectionsStrings = lines[i].split(" ")
                val startLabel = connectionsStrings[0]
                val symbolLabel = connectionsStrings[1]
                val endLabel = connectionsStrings[2]

                states[startLabel]?.connections?.set(Pair(symbolLabel, endLabel), endLabel)
            }
        }

        // Generate the automata grammar from regular grammar
//        fun generateAutomataFrom(filePath: String): String {
//
//            // Parts of automata
//            var allStates = ""
//            var allSymbols = ""
//            var initialStates = ""
//            var finalStates = ""
//            var transitions = ""
//
//
//            // read file contents
//            fileContent = File(filePath).readText()
//            val fileLines = fileContent.lines()
//
//            // Insert a final State to the automata
//            val finalState = "FINAL"
//            allStates = "${fileLines[0]} $finalState\n"
//
//            // Symbols, initial nodes stay the same
//            allSymbols = "${fileLines[1]}\n"
//            initialStates = "${fileLines[2]}\n"
//
//            // We create the final node
//            finalStates = "$finalState\n"
//
//            // read connections for each state
//            for (i in 3..<fileLines.size) {
//
//                val wordCount = fileLines[i].split("\\s+".toRegex()).count()
//
//                // If the word count is only two, we have to insert the final Node
//                val currentLine = fileLines[i]
//                if(wordCount == 2) {
//                    transitions += "$currentLine $finalState\n"
//                } else {
//                    transitions += "$currentLine\n"
//                }
//            }
//
//            var returnValue = allStates + allSymbols + initialStates + finalStates + transitions
//            returnValue = returnValue.reversed().replaceFirst("\n","").reversed()
//
//
//
//            return returnValue
//        }

        // Generate DOT code to represent the automata
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
            return dotCode
        }

        // Eliminate unreachable states
//        fun eliminateUnreachableStates() : String {
//
//            var globallyVisited = mutableSetOf<String>()
//            var globallyVisitedEdges = mutableSetOf<String>()
//
//            // Perform a BFS on the automata graph for each entry point
//            for(entryPoint in initialLabels) {
//                var visitedStates = mutableSetOf<String>()
//                var queue = mutableListOf<String>()
//
//                queue.add(entryPoint)
//                while(queue.isNotEmpty()) {
//                    val currentStateLabel = queue.removeAt(0)
//                    val currentConnections = states[currentStateLabel]?.connections
//
//                    if (currentConnections != null) {
//                        for((symbol, endStateLabel) in currentConnections.keys) {
//                            if(endStateLabel !in visitedStates) {
//                                visitedStates.add(endStateLabel)
//                                globallyVisited.add(endStateLabel)
//                                queue.add(endStateLabel)
//                            }
//                            if(symbol !in globallyVisitedEdges) {
//                                globallyVisitedEdges.add(symbol)
//                            }
//                        }
//                    }
//                }
//            }
//
//            // Create the list of unvisited states
//            val unVisitedStates = mutableListOf<String>()
//            for(key in states.keys) {
//                if(key !in globallyVisited && key !in initialLabels) {
//                    unVisitedStates.add(key)
//                }
//            }
//
//            // Create automata grammar for the new system
//            val allStates = states.keys.filter { state -> state !in unVisitedStates }.toString().replace("[","").replace("]","").replace(",","") + "\n"
//            val allSymbols = globallyVisitedEdges.toString().replace("[","").replace("]","").replace(",","") + "\n"
//            val initStates = initialLabels.toString().replace("[","").replace("]","").replace(",","") + "\n"
//            val endStates = finalLabels.toString().replace("[","").replace("]","").replace(",","") + "\n"
//
//            // read connections for each state
//            var transitions = ""
//            val lines = fileContent.lines()
//            for (i in 4..<lines.size) {
//                val connectionsStrings = lines[i].split(" ")
//                val startLabel = connectionsStrings[0]
//                val symbolLabel = connectionsStrings[1]
//                val endLabel = connectionsStrings[2]
//
//                if(startLabel !in unVisitedStates && endLabel !in unVisitedStates) {
//                    transitions += "${lines[i]}\n"
//                }
//            }
//
//            return allStates + allSymbols + initStates + endStates + transitions
//        }

        // Erases the unproductive nodes and its transitions
//        fun eliminateNonProductiveStates(): String {
//            var globallyVisited = mutableSetOf<String>()
//            var globallyVisitedEdges = mutableSetOf<String>()
//
//            // Perform a BFS on the automata graph for each end point
//            for(endPoint in finalLabels) {
//                var visitedStates = mutableSetOf<String>()
//                var queue = mutableListOf<String>()
//
//                queue.add(endPoint)
//                while(queue.isNotEmpty()) {
//                    val currentStateLabel = queue.removeAt(0)
//                    val currentConnections = getPreviousStates(currentStateLabel)
//
//                    for((prevStateLabel, symbol) in currentConnections) {
//                        if(prevStateLabel !in visitedStates) {
//                            visitedStates.add(prevStateLabel)
//                            globallyVisited.add(prevStateLabel)
//                            queue.add(prevStateLabel)
//                        }
//                        if(symbol !in globallyVisitedEdges) {
//                            globallyVisitedEdges.add(symbol)
//                        }
//                    }
//                }
//            }
//
//            // Create the list of unvisited states
//            val unVisitedStates = mutableListOf<String>()
//            for(key in states.keys) {
//                if(key !in globallyVisited && key !in finalLabels) {
//                    unVisitedStates.add(key)
//                }
//            }
//
//            // Create automata grammar for the new system
//            val allStates = states.keys.filter { state -> state !in unVisitedStates }.toString().replace("[","").replace("]","").replace(",","") + "\n"
//            val allSymbols = globallyVisitedEdges.toString().replace("[","").replace("]","").replace(",","") + "\n"
//            val initStates = initialLabels.toString().replace("[","").replace("]","").replace(",","") + "\n"
//            val endStates = finalLabels.toString().replace("[","").replace("]","").replace(",","") + "\n"
//
//            // read connections for each state
//            var transitions = ""
//            val lines = fileContent.lines()
//            for (i in 4..<lines.size) {
//                val connectionsStrings = lines[i].split(" ")
//                val startLabel = connectionsStrings[0]
//                val symbolLabel = connectionsStrings[1]
//                val endLabel = connectionsStrings[2]
//
//                if(startLabel !in unVisitedStates && endLabel !in unVisitedStates) {
//                    transitions += "${lines[i]}\n"
//                }
//            }
//
//            return allStates + allSymbols + initStates + endStates + transitions
//        }

        // From a list of words, returns only those the automata can create
        fun findCreatableWords(words: List<String>): List<String> {

            val correctWords = mutableListOf<String>() // correct words are the ones the automata can create

            // check for each word if its creatable
            for (word in words){
                if(isCreatable(word)) {
                    correctWords.add(word)
                }
            }
            return correctWords
        }

        // Gets the states previous to the current one
        private fun getPreviousStates(stateLabel: String): MutableList<Pair<String, String>> {
            var list = mutableListOf<Pair<String,String>>()

            for ((prevState, stateData) in states){
                for(con in stateData.connections.keys){
                    if(con.second == stateLabel){
                        list.add(Pair(prevState, con.first))
                    }
                }
            }
            return list
        }

    fun genImage(outputFileName: String) {
        val dotCode = generateDotCode()
        Runtime.getRuntime().exec("echo HEllo WOrlds!")
        val genImgCommand = "echo $dotCode | dot -T png > src/test/out/$outputFileName.png"
        Runtime.getRuntime().exec(genImgCommand)
    }

        // Checks if the words can be created by the automata
        private fun isCreatable(word: String): Boolean {
            var found = false

            // Perform a BFS on the automata graph for each entry point
            for(entryPoint in initialLabels) {
                var queue = mutableListOf<Pair<String, Int>>() // Use Pair to store both state and depth

                queue.add(Pair(entryPoint, 0)) // Start at depth 0

                while (queue.isNotEmpty() && !found) {
                    val (currentStateLabel, depth) = queue.removeAt(0)
                    val currentConnections = states[currentStateLabel]?.connections

                    if(currentStateLabel in finalLabels && word.length == depth){
                        found = true
                        break
                    }

                    if (currentConnections != null && depth < word.length) {
                        for ((symbol, endStateLabel) in currentConnections.keys) {
                            if(symbol == eps) {
                                queue.add(Pair(endStateLabel, depth))
                            }
                            else if(word[depth].toString() == symbol) {
                                queue.add(Pair(endStateLabel, depth + 1)) // Increment depth when visiting a new state
                            }
                        }
                    }
                }
            }
            return found
        }

        fun readFileLinesToList(fileName: String): List<String> {
            val lines = mutableListOf<String>()

            try {
                File(fileName).useLines { lines.addAll(it) }
            } catch (e: Exception) {
                // Handle any exceptions that may occur during file reading (e.g., FileNotFoundException)
                e.printStackTrace()
            }

            return lines
        }

        // Safely load a new stateMachine
        fun load(file: File) {
            clear()
            loadStates(file)
        }

        private fun clear() {
            symbols.clear()
            initialLabels.clear()
            finalLabels.clear()
        }
}