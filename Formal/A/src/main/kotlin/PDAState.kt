package main.kotlin

class PDAState(val label: String) {
    var initial: Boolean = false
    var final: Boolean = false
    var outgoing: MutableMap<Pair<String, String>, MutableSet<Pair<String, List<String>>>> = mutableMapOf()

    fun addConnection(nextLabel: String, symbol: String, popStack: String, pushStack: List<String>) {
        val key = symbol to popStack

        if (outgoing[key] == null) {
            outgoing[key] = mutableSetOf()
        }

        outgoing[key]!!.add(nextLabel to pushStack)
    }
}
