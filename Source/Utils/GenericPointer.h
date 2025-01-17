#pragma once

struct GenericPointer {
    template <typename T>
    explicit(false) GenericPointer(T* pointer) noexcept
        : value{(void*)pointer}
    {
    }

    GenericPointer() = default;

    template <typename T>
    [[nodiscard]] T as() const noexcept
    {
        return T(value);
    }

private:
    void* value{};
};
