package test.kotlin

import StateMachine
import java.io.File

fun main(){
    var before = ""
    var after = ""
    val outputFilePath = "src/test/out/out4.txt"
    val outPutFile = File(outputFilePath)

    StateMachine.load("src/test/resources/form_I.A.4.txt")
    before = StateMachine.generateDotCode()
    after = StateMachine.eliminateNonProductiveStates()
    after = after.reversed().replaceFirst("\n","").reversed()
    println(before)
    outPutFile.writeText(after)

    StateMachine.load(outputFilePath)
    after = StateMachine.generateDotCode()
    outPutFile.writeText(after)
    println(after)
}