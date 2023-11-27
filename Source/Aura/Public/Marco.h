#pragma once

//// If this then that

#define IF_THIS_THEN_THAT(Condition, Do) if ((Condition)) Do

// Conditions

#define IS_VALID_OBJECT(Object) (::IsValid(Object))
#define IS_INVALID_OBJECT(Object) (!IS_VALID_OBJECT(Object))
#define IS_VALID_POINTER(Pointer) (Pointer.IsValid())
#define IS_INVALID_POINTER(Pointer) (!IS_VALID_POINTER(Pointer))
#define IS_TRUE(Condition) (Condition)
#define IS_FALSE(Condition) (!IS_TRUE(Condition))

// Dos

#define RETURN_VOID {return;}
#define RETURN_OBJECT(Object) {return Object;}
#define CONTINUE {continue;}
#define SET_OBJECT(Object, InObject) {Object = InObject;}

// Defs

#define VALID_THEN_THAT(Object, Do) IF_THIS_THEN_THAT(IS_VALID_OBJECT(Object), Do)

#define INVALID_RETURN_VOID(Object)  IF_THIS_THEN_THAT(IS_INVALID_OBJECT(Object), RETURN_VOID)
#define INVALID_RETURN_OBJECT(Object, Ret) IF_THIS_THEN_THAT(IS_INVALID_OBJECT(Object), RETURN_OBJECT(Ret))
#define INVALID_CONTINUE(Object) IF_THIS_THEN_THAT(IS_INVALID_OBJECT(Object), CONTINUE)

#define INVALID_POINTER_RETURN_VOID(Pointer)  IF_THIS_THEN_THAT(IS_INVALID_POINTER(Object), RETURN_VOID)
#define INVALID_POINTER_RETURN_OBJECT(Pointer, Ret) IF_THIS_THEN_THAT(IS_INVALID_POINTER(Object), RETURN_OBJECT(Ret))
#define INVALID_POINTER_CONTINUE(Pointer) IF_THIS_THEN_THAT(IS_INVALID_POINTER(Object), CONTINUE)

#define TRUE_RETURN_VOID(Condition) IF_THIS_THEN_THAT(IS_TRUE(Condition), RETURN_VOID)
#define FALSE_RETURN_VOID(Condition) IF_THIS_THEN_THAT(IS_FALSE(Condition), RETURN_VOID)
#define FALSE_RETURN_OBJECT(Condition, Ret) IF_THIS_THEN_THAT(IS_FALSE(Condition), RETURN_OBJECT(Ret))

//// Setters & Getters

// Getters

#define VALUE_GETTER(Property) FORCEINLINE_DEBUGGABLE auto Get##Property() const RETURN_OBJECT(Property)
#define CONST_VALUE_GETTER(Property) const VALUE_GETTER(Property)
#define VALUE_GETTER_FUNC_NAME(Property, FuncName) FORCEINLINE_DEBUGGABLE auto FuncName() const RETURN_OBJECT(Property)

#define REF_GETTER(Property) FORCEINLINE_DEBUGGABLE auto& Get##Property() RETURN_OBJECT(Property)
#define CONST_REF_GETTER(Property) const FORCEINLINE_DEBUGGABLE auto& Get##Property() const RETURN_OBJECT(Property)
#define STATIC_REF_GETTER(Property) static REF_GETTER(Property)
#define STATIC_CONST_REF_GETTER(Property) static CONST_REF_GETTER(Property)

// Setters

#define SETTER(Property) FORCEINLINE_DEBUGGABLE void Set##Property(const auto& In##Property) SET_OBJECT(Property, In##Property)
#define SETTER_FUNC_NAME(Property, FuncName) FORCEINLINE_DEBUGGABLE void FuncName(const auto& In##Property) SET_OBJECT(Property, In##Property)