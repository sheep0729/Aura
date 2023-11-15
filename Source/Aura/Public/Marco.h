#pragma once

#define IF_THIS_THEN_THAT(Condition, Do) \
	if ((Condition)) {      \
		Do                  \
	}

#define VALID_THEN_THAT(Object, Do) IF_THIS_THEN_THAT(IsValid(Object), Do)
#define INVALID_THEN_THAT(Object, Do) IF_THIS_THEN_THAT(!IsValid(Object), Do)
#define INVALID_POINTER_THEN_THAT(Pointer, Do) IF_THIS_THEN_THAT(!Pointer.IsValid(), Do)
#define TRUE_THEN_THAT(Value, Do) IF_THIS_THEN_THAT(Value, Do)
#define FALSE_THEN_THAT(Value, Do) IF_THIS_THEN_THAT(!(Value), Do)

#define INVALID_RETURN_VOID(Object)  INVALID_THEN_THAT(Object, return;)
#define INVALID_RETURN_VALUE(Object, Value) INVALID_THEN_THAT(Object,return Value;)
#define INVALID_CONTINUE(Object) INVALID_THEN_THAT(Object,continue;)

#define INVALID_POINTER_RETURN_VOID(Pointer)  INVALID_POINTER_THEN_THAT(Pointer, return;)
#define INVALID_POINTER_RETURN_VALUE(Pointer, Value) INVALID_POINTER_THEN_THAT(Pointer,return Value;)
#define INVALID_POINTER_CONTINUE(Pointer) INVALID_POINTER_THEN_THAT(Pointer,continue;)

#define TRUE_RETURN_VOID(Value) TRUE_THEN_THAT(Value, return;)

#define FALSE_RETURN_VOID(Value) FALSE_THEN_THAT(Value, return;)
#define FALSE_RETURN_VALUE(Value, Ret) FALSE_THEN_THAT(Value, return Ret;)

#define VALUE_GETTER_FUNC_NAME(Property, FuncName)       \
	FORCEINLINE_DEBUGGABLE auto FuncName() const { \
		return Property;                                \
	}

#define VALUE_BLUEPRINT_GETTER(Property)                          \
	UFUNCTION(BlueprintGetter) \
	FORCEINLINE_DEBUGGABLE auto Get##Property() const { \
		return Property;                                \
	}

#define VALUE_GETTER(Property)                          \
	FORCEINLINE_DEBUGGABLE auto Get##Property() const { \
		return Property;                                \
	}

#define CONST_VALUE_GETTER(Property)                          \
	FORCEINLINE_DEBUGGABLE const auto Get##Property() const { \
		return Property;                                \
	}

#define STATIC_CONST_REF_GETTER(Property)                       \
	FORCEINLINE_DEBUGGABLE static const auto& Get##Property() { \
		return Property;                                        \
	}

#define CONST_REF_BLUEPRINT_GETTER(Property)                    \
	CONST_REF_GETTER_UFUNCTION(Property, BlueprintGetter)

#define CONST_REF_GETTER_UFUNCTION(Property, ...)               \
	UFUNCTION(__VA_ARGS__)		                                \
	CONST_REF_GETTER(Property)

#define CONST_REF_GETTER(Property)                             \
	FORCEINLINE_DEBUGGABLE const auto& Get##Property() const { \
	    return Property;                                       \
	}

#define REF_GETTER(Property)                             \
	FORCEINLINE_DEBUGGABLE auto& Get##Property() {       \
		return Property;                                 \
	}

#define STATIC_REF_GETTER(Property) static REF_GETTER(Property)

#define SETTER_FUNC_NAME(Property, FuncName)                                  \
	FORCEINLINE_DEBUGGABLE void FuncName(const auto& In##Property) { \
		Property = In##Property;                                          \
	}

#define SETTER(Property)                                                  \
	FORCEINLINE_DEBUGGABLE void Set##Property(const auto& In##Property) { \
		Property = In##Property;                                          \
	}

#define PUBLIC public:
#define PRIVATE private:
#define PROTECTED protected: