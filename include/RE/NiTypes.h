#pragma once


namespace RE
{
	// 18
	template <typename T>
	class NiTLargeArray
	{
	public:
		NiTLargeArray();
		virtual ~NiTLargeArray();

		// fast, doesn't search for empty slots
		void Append(T item)
		{
			if (m_emptyRunStart == m_arrayBufLen) {
				// need to expand the array
				Resize(m_arrayBufLen + 1);
			}

			m_data[m_emptyRunStart] = item;
			m_emptyRunStart++;
			m_size++;
		}

		void Resize(UInt32 size)
		{
			// not reclaiming memory yet
			if (size <= m_size) return;

			// obey min grow size
			UInt32	growSize = size - m_size;
			if (growSize < m_growSize)
				growSize = m_growSize;

			size = m_arrayBufLen + growSize;

			// create new array
			T	* newData = (T *)FormHeap_Allocate(sizeof(T) * size);

			for (UInt32 i = 0; i < size; i++) {
				new (&newData[i]) T;
				newData[i] = 0;
			}

			// copy over data, compacting as we go
			UInt32	iter = 0;

			for (UInt32 i = 0; i < m_emptyRunStart; i++) {
				if (m_data[i]) {
					newData[iter] = m_data[i];
					iter++;
				}
			}

			// update pointers
			T		* oldData = m_data;
			UInt32	oldDataLen = m_emptyRunStart;

			m_data = newData;
			m_arrayBufLen = size;
			m_emptyRunStart = m_size;

			// delete old array
			if (oldData) {
				for (UInt32 i = 0; i < oldDataLen; i++)
					if (oldData[i])
						oldData[i].~T();

				FormHeap_Free(oldData);
			}
		}

		//void	** _vtbl;			// 00
		T		* m_data;			// 04
		UInt32	m_arrayBufLen;		// 08 - max elements storable in m_data
		UInt32	m_emptyRunStart;	// 0C - index of beginning of empty slot run
		UInt32	m_size;				// 10 - number of filled slots
		UInt32	m_growSize;			// 14 - number of slots to grow m_data by
	};


	template <class T>
	class NiTLargePrimitiveArray : public NiTLargeArray<T>
	{
	public:
		NiTLargePrimitiveArray(unsigned int uiMaxSize = 0, unsigned int uiGrowBy = 1);
	};
}
