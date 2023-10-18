class State(val label: String) {
    var isInitial: Boolean = false
    var isFinal: Boolean = false
    var connections: MutableMap<Pair<String, String>, String> = mutableMapOf()
}