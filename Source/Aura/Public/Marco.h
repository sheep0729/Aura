#pragma once

#define IF_THIS_THEN_THAT(Condition, Do) \
	if ((Condition)) {      \
		Do                  \
	}

#define NULL_THEN_THAT(Pointer, Do) IF_THIS_THEN_THAT(Pointer == nullptr, Do)
#define TRUE_THEN_THAT(Value, Do) IF_THIS_THEN_THAT(Value, Do)
#define FALSE_THEN_THAT(Value, Do) IF_THIS_THEN_THAT(!(Value), Do)

#define NULL_RETURN_VOID(Pointer)  NULL_THEN_THAT(Pointer, return;)
#define NULL_RETURN_VALUE(Pointer, Value) NULL_THEN_THAT(Pointer,return Value;)
#define NULL_CONTINUE(Pointer) NULL_THEN_THAT(Pointer,continue;)

#define TRUE_RETURN_VOID(Value) TRUE_THEN_THAT(Value, return;)

#define FALSE_RETURN_VOID(Value) FALSE_THEN_THAT(Value, return;)
#define FALSE_RETURN_VALUE(Value, Ret) FALSE_THEN_THAT(Value, return Ret;)

#define VALUE_GETTER(Property)                          \
	FORCEINLINE auto Get##Property() const { \
		return Property;                                \
	}

#define STATIC_CONST_REF_GETTER(Property)                       \
	FORCEINLINE static const auto& Get##Property() { \
		return Property;                                        \
	}

#define CONST_REF_GETTER(Property)                             \
	FORCEINLINE const auto& Get##Property() const { \
	    return Property;                                       \
	}

#define REF_GETTER(Property)                             \
	FORCEINLINE auto& Get##Property() {       \
		return Property;                                 \
	}

#define SETTER(Property)                                                  \
	FORCEINLINE void Set##Property(const auto& In##Property) { \
		Property = In##Property;                                          \
	}