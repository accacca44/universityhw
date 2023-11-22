package test.kotlin

import StateMachine
import main.kotlin.NewStateMachine
import java.io.File

fun main(){
    var before = ""
//    var after = ""
//    val outputFilePath = "src/test/out/out3.txt"
//    val outPutFile = File(outputFilePath)
//
//    StateMachine.load("src/test/resources/form_I.A.3.txt")
//    before = StateMachine.generateDotCode()
//    after = StateMachine.eliminateNonProductiveStates()
//    after = after.reversed().replaceFirst("\n","").reversed()
//    println(before)
//    outPutFile.writeText(after)
//
//    StateMachine.load(outputFilePath)
//    after = StateMachine.generateDotCode()
//    outPutFile.writeText(after)
//    println(after)

    val sm1 = NewStateMachine(File("src/test/resources/form_I.A.3.txt"))
    val sm2 = sm1.eliminateNonProductiveStates()
    sm2.generateDotCode()
}