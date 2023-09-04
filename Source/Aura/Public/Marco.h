#pragma once

#define NULL_RETURN_VOID(Pointer)    \
	if (Pointer == nullptr)          \
	{                                \
		return;                      \
	}

#define NULL_RETURN_VALUE(Pointer, Value) \
	if (Pointer == nullptr)               \
	{                                     \
		return Value;                     \
	}

#define TRUE_RETURN_VOID(Value)      \
	if (Value)                       \
	{                                \
		return;                      \
	}

#define FALSE_RETURN_VOID(Value)     \
	if (!(Value))                    \
	{                                \
		return;                      \
	}

#define FALSE_RETURN_Value(Value, Ret) \
	if (!(Value))                      \
	{                                  \
		return Ret;                    \
	}

#define VALUE_GETTER(Property)                          \
	FORCEINLINE_DEBUGGABLE auto Get##Property() const { \
		return Property;                                \
	}

#define STATIC_CONST_REF_GETTER(Property)                       \
	FORCEINLINE_DEBUGGABLE static const auto& Get##Property() { \
	return Property;                                            \
	}

#define CONST_REF_GETTER(Property)                             \
	FORCEINLINE_DEBUGGABLE const auto& Get##Property() const { \
	    return Property;                                       \
	}

#define REF_GETTER(Property)                             \
	FORCEINLINE_DEBUGGABLE auto& Get##Property() {       \
		return Property;                                 \
	}

#define SETTER(Property)                                                  \
	FORCEINLINE_DEBUGGABLE void Set##Property(const auto& In##Property) { \
		Property = In##Property;                                          \
	}