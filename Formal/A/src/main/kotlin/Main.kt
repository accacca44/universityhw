fun main() {
    StateMachine.loadStates("src/main/resources/form_I.A.4_2.txt")
    print(StateMachine.generateDotCode())

    val lines = StateMachine.readFileLinesToList("src/main/resources/form_I.A.4_2_szavak.txt")
    val correctWords = StateMachine.findCreatableWords(lines)
    println(correctWords)
}