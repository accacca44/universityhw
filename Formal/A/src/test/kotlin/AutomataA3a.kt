package test.kotlin

import StateMachine
import java.io.File

fun main(){
    var before = ""
    var after = ""
    val outputFilePath = "src/test/out/out3.txt"
    val outPutFile = File(outputFilePath)

    StateMachine.load("src/test/resources/form_I.A.3.txt")
    before = StateMachine.generateDotCode()
    after = StateMachine.eliminateUnreachableStates()
    after = after.reversed().replaceFirst("\n","").reversed()
    println(before)
    outPutFile.writeText(after)

    StateMachine.load(outputFilePath)
    after = StateMachine.generateDotCode()
    outPutFile.writeText(after)
    println(after)
}