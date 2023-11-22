package test.kotlin

import main.kotlin.NewStateMachine
import java.io.File

fun main() {
    val sm1 = NewStateMachine(File("src/test/resources/form_I.B.1_a1.txt"))
    val sm2 = NewStateMachine(File("src/test/resources/form_I.B.1_a2.txt"))
    println(sm1.isEquivalent(sm2))

    val sm3 = NewStateMachine(File("src/test/resources/form_I.B.1_b1.txt"))
    val sm4 = NewStateMachine(File("src/test/resources/form_I.B.1_b2.txt"))
    println(sm3.isEquivalent(sm4))

    val sm5 = NewStateMachine(File("src/test/resources/form_I.B.1_c1.txt"))
    val sm6 = NewStateMachine(File("src/test/resources/form_I.B.1_c2.txt"))
    println(sm5.isEquivalent(sm6))
}