/***** Autogenerated from runarray.in; changes will be overwritten *****/

#ifndef runarray_H
#define runarray_H
namespace run {
void emptyArray(vm::stack *);
void newDeepArray(vm::stack *);
void newInitializedArray(vm::stack *);
void newAppendedArray(vm::stack *);
void copyArray0(vm::stack *);
void copyArray1(vm::stack *);
void copyArray2(vm::stack *);
void arrayRead(vm::stack *);
void arraySliceRead(vm::stack *);
void arraySliceReadToEnd(vm::stack *);
void arrayArrayRead(vm::stack *);
void arrayWrite(vm::stack *);
void arraySliceWrite(vm::stack *);
void arraySliceWriteToEnd(vm::stack *);
void arrayLength(vm::stack *);
void arrayKeys(vm::stack *);
void arrayCyclicFlag(vm::stack *);
void arraySetCyclicFlag(vm::stack *);
void arrayInitializedHelper(vm::stack *);
void arrayInitialized(vm::stack *);
void arrayCyclicHelper(vm::stack *);
void arrayCyclic(vm::stack *);
void arrayPushHelper(vm::stack *);
void arrayPush(vm::stack *);
void arrayAppendHelper(vm::stack *);
void arrayAppend(vm::stack *);
void arrayPopHelper(vm::stack *);
void arrayPop(vm::stack *);
void arrayInsertHelper(vm::stack *);
void arrayInsert(vm::stack *);
void arrayDelete(vm::stack *);
void arrayAlias(vm::stack *);
void arrayIntArray(vm::stack *);
void arraySequence(vm::stack *);
void arrayFunction(vm::stack *);
void arraySort(vm::stack *);
void arrayCopy(vm::stack *);
void arrayConcat(vm::stack *);
void array2Copy(vm::stack *);
void array3Copy(vm::stack *);
void array2Transpose(vm::stack *);
void array3Transpose(vm::stack *);
void arrayConditional(vm::stack *);
}

#endif // runarray_H
