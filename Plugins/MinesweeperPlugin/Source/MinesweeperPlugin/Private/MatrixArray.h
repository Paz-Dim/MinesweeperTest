#pragma once

#include "CoreMinimal.h"

/* Matrix class, based on standard TArray. Adds methods to work with array as matrix. */
template<typename T>
class FMatrixArray : public TArray<T>
{
public:
    // Methods
    // Get matrix size (width, height)
    TPair<int32, int32> getSize() const
    {
        return TPair<int32, int32>(m_width, m_height);
    }
    // Set matrix size
    void setSize(int32 width, int32 height)
    {
        m_width = width;
        m_height = height;
        TArray<T>::SetNum(m_width * m_height);
    }
    void setSize(int32 width, int32 height, T defaultValue)
    {
        m_width = width;
        m_height = height;
        TArray<T>::Init(defaultValue, m_width * m_height);
    }
    // Get/Set elem. Doesn't check size.
    const T &getElem(int32 x, int32 y) const
    {
        return TArray<T>::operator[](x + y * m_width);
    }
    const T &getElem(const FIntPoint &pos) const
    {
        return TArray<T>::operator[](pos.X + pos.Y * m_width);
    }
    void setElem(int32 x, int32 y, const T &elem)
    {
        TArray<T>::operator[](x + y * m_width) = elem;
    }
    // Get element index in TArray from coordinates
    int32 getElemIndex(int32 x, int32 y) const
    {
        return x + y * m_width;
    }
    // Get element coordinates by index in TArray
    TPair<int32, int32> getElemCoords(int32 index) const
    {
        return TPair<int32, int32>(index % m_width, index / m_width);
    }

private:
    // Fields
    // Matrix size
    int32 m_width {0};
    int32 m_height {0};
};