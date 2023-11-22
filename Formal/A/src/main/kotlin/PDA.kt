package main.kotlin

import java.io.File

class PDA() {
    private val states: MutableMap<String, PDAState> = mutableMapOf()
    private var stateLabels: MutableSet<String> = mutableSetOf()
    private var alphabet: MutableSet<String> = mutableSetOf()
    private var stackSymbols: MutableSet<String> = mutableSetOf()
    private var initialStateLabel: String = ""
    private var initialStackSym: String = ""
    private var finalStates: MutableSet<String> = mutableSetOf()
    private var eps = "eps"

    fun load(inputFile: File) {
        val fileContent = inputFile.readText().lines()

        stateLabels = fileContent[0].split(" ").toMutableSet()

        for (stateLabel in stateLabels) {
            states[stateLabel] = PDAState(stateLabel)
        }

        alphabet = fileContent[1].split(" ").toMutableSet()
        stackSymbols = fileContent[2].split(" ").toMutableSet()

        initialStateLabel = fileContent[3].trim()
        states[initialStateLabel]?.initial = true

        initialStackSym = fileContent[4].trim()

        finalStates = fileContent[5].split(" ").toMutableSet()
        finalStates.forEach { stateLabel ->
            states[stateLabel]?.final = true
        }

        for (i in 6..<fileContent.size) {
            val line = fileContent[i]
            val tokens = line.split(" ")
            val startLabel = tokens[0]
            val symbol = tokens[1]
            val popStack = tokens[2]
            val pushStack = tokens.subList(3, tokens.size - 1)
            val endLabel = tokens.last()
            states[startLabel]?.addConnection(endLabel, symbol, popStack, pushStack)
        }
    }


    fun matchWord(word: String): List<String>? {
        return matchStates(word, mutableListOf(initialStateLabel), mutableListOf(initialStackSym))
    }

    private fun matchStates(word: String, states: MutableList<String>, stack: MutableList<String>): List<String>? {
        // Set the current state from the path
        val currentState = states.last()

        // Check if the word is completed
        if (word.isEmpty()) {
            val matched = (finalStates.isEmpty() && stack.isEmpty()) || (currentState in finalStates || stack.isEmpty())
            if (matched) {
                return states
            }
        }

        // If no more symbols are in the stack then return null
        if (stack.isEmpty()) {
            return null
        }

        // Stack TOP
        val currentStackSym = stack.removeAt(stack.size - 1)

        // Next valid symbols are the EPS and the next char of the input word
        val nextSymbols = mutableListOf<String>()
        if (word.isNotEmpty()) {
            nextSymbols.add(word[0].toString())
        }
        nextSymbols.add(eps) // Assuming EPS_SYM_IN is an 'eps' string

        // Filter transitions for valid symbol + stackSymbol
        val nextKeys: MutableList<Pair<String, String>> = mutableListOf()
        for ( sym in nextSymbols) {
            val newPair = Pair(sym, currentStackSym)
            if (this.states[currentState]?.outgoing?.contains(newPair) == true) {
                nextKeys.add(newPair)
            }
        }

        // Move with every possible transition and then backtrack
        for ( key in nextKeys) {
            for ( (nextStateLabel, pushStack) in this.states[currentState]!!.outgoing[key]!!) {
                val nextWord = if (key.first == eps) word else word.substring(1)
                states.add(nextStateLabel)
                val nextStates = states.toMutableList()
                val nextStack = stack.toMutableList()
                for (ps in pushStack) {
                    if (ps != eps) {
                        nextStack.add(ps)
                    }
                }

                val match = matchStates(nextWord, nextStates, nextStack)
                if (match != null) {
                    return match
                }
            }
        }
        return null
    }
}


