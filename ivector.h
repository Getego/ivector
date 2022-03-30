/*--------------------------------------------------------------------------------------------------*/
/*      Autor: Georgios Terzoglou                                                                   */
/*      Copyright (©) 2014 by Georgios Terzoglou                                                    */
/*      Bug-reports and suggestions to georgios.terzoglou@googlemail.com                            */
/*                                                                                                  */
/*                                                                                                  */
/*                                                                                                  */
/*      GENERAL NOTE: I assume no liability for any damages with this header.                       */
/*      Using this header at your own risk.                                                         */
/*                                                                                                  */
/*                                                                                                  */
/*      FROM THE LINE 151 TO THE END OF THIS HEADER MODIFICATIONS ARE PROHIBITED !!                 */
/*                                                                                                  */
/*                                                                                                  */
/*                                                                                                  */
/*      Template class: iVector<T>                                                                  */
/*                                                                                                  */
/*                                                                                                  */
/*      Version:       1.2.8.0473                                                                   */
/*                                                                                                  */
/*                                                                                                  */
/*      State:         Release candidate [RC]                                                       */
/*      Date:          09.06.2014 [Last changes]                                                    */
/*                                                                                                  */
/*      iVectors are sequence containers representing arrays that can change in size.               */
/*      Just like arrays, iVectors use contiguous storage locations for their elements,             */
/*      which means that their elements can also be accessed using offsets on regular               */
/*      pointers to its elements, and just as efficiently as in arrays. But unlike arrays,          */
/*      their size can change dynamically, with their storage being handled automatically           */
/*      by the container. Internally, iVectors use a dynamically allocated array to store           */
/*      their elements. This array may need to be reallocated in order to grow in size when         */
/*      new elements are inserted, which implies allocating a new array and moving all              */
/*      elements to it. This is a relatively expensive task in terms of processing time,            */
/*      and thus, iVectors do not reallocate each time an element is added to the container.        */
/*      Instead, iVector containers may allocate some extra storage to accommodate for possible     */
/*      growth, and thus the container may have an actual capacity greater than the storage         */
/*      strictly needed to contain its elements (i.e., its size). Libraries can implement           */
/*      different strategies for growth to balance between memory usage and reallocations,          */
/*      but in any case, reallocations should only happen at logarithmically growing intervals      */
/*      of size so that the insertion of individual elements at the end of the iVector can be       */
/*      provided with amortized constant time complexity (see push_back). Therefore, compared       */
/*      to arrays, iVectors consume more memory in exchange for the ability to manage storage       */
/*      and grow dynamically in an efficient way. Compared to the other dynamic sequence            */
/*      containers (deques, lists and forward_lists), iVectors are very efficient accessing its     */
/*      elements (just like arrays) and relatively efficient adding or removing elements from       */
/*      its end. For operations that involve inserting or removing elements at positions other      */
/*      than the end, they perform worse than the others, and have less consistent iterators and    */
/*      references than lists and forward_lists.                                                    */
/*--------------------------------------------------------------------------------------------------*/

/** iVector use different settings for memory management if desired. **/

/** INFORMATION: For personalized memory Settings looking this lines 128  -  147

  * NOTE: It is not recommended to modify the settings. They could thus degrade the
		  speed greatly. Keep in mind that by doing these settings apply to all objects!

	* switch for memory management system:        129  -  130
	* General Settings:                           132  -  133
	* Constant overflow management settings:      135  -  139
	* Dynamic overflow management:                141  -  146
*/

/* Important informations about the different iterator types:
 *
 *	The following iterators are working:
 *		- itarator
 *		- const_itarator
 *		- reverse_iterator
 *		- const_reverse_iterator
 *
 * The reverse_iterator_t is an iterator adaptor that reverses the direction of a given iterator.
 * In other words, when provided with a bidirectional iterator, REVERSE_ITERATOR produces a
 * new iterator that moves from the end to the beginning of the sequence defined by the underlying
 * bidirectional iterator. For a reverse iterator r constructed from an iterator i,
 * the relationship &*r == &*(i-1) is always true; thus a reverse iterator constructed from a
 * one-past-the-end iterator dereferences to the last element in a sequence. This is the iterator
 * returned by member functions rbegin() and rend() of the iVector<T> container.
*/

/** Constant overflow management

	* explanation the constant concepts:
	-----------------------------------------------------------
	* MINIMAL_OVERFLOW           = minimum space required above
	* MAXIMAL_OVERFLOW           = maximum space required above
	* REMOVE_IF_IT_IS_LARGER     = limit,delete too much memory

 * Activate the constant mode: Ensure the line 130 is commented out!
 * commented out: "#define GT_ACTIVATE_AUTOMATIC_MODE_FOR_OVERFLOW"
 * looking on line 130
*/

/** Dynamic overflow management

	* Optimized iVector settings:
	* You can used the GT::iVector<T> in the same
	* memory allocation settings as std::vector<T>. (See: Authentic std::vector settings)
	* In the optimized GT::iVector<T> settings are used greater memory steps
	* then std::vector<T> and a greater startvelue of allocated memory. (More speed)
	* If you know the maximum size of your GT::iVector<T> use this startvalue for maximum speed.

	* Authentic std::vector settings:		 * Optimized GT::iVector settings:
	---------------------------------		 ---------------------------------
	* FIRST_RESERVE_AMOUNT        = 0              * FIRST_RESERVE_AMOUNT        = 16
	* AUTO_MINIMAL_OVERFLOW       = 0              * AUTO_MINIMAL_OVERFLOW       = 0
	* AUTO_MAXIMAL_OVERFLOW       = 26             * AUTO_MAXIMAL_OVERFLOW       = 26
	* ADJUST_BASE_NUMBER          = 1              * ADJUST_BASE_NUMBER          = 1
	* INITIAL_BASE_VALUE          = 0              * INITIAL_BASE_VALUE          = 4
	 ---------------------------------		 ---------------------------------

 * The dynamic mode is recommended!

 * Activate the dynamic mode: Ensure the line 130 is commented in!
 * commented in: "#define  GT_ACTIVATE_AUTOMATIC_MODE_FOR_OVERFLOW"
 * looking on line 130
*/

#ifndef IVECTOR_H
#define IVECTOR_H

// ------------------------------------MEMORY-SETTINGS-BEGIN------------------------------------ //
/* switch for memory management system. [check out the line at 93 or 118] */
#define GT_ACTIVATE_AUTOMATIC_MODE_FOR_OVERFLOW      // Switch the Memory management mode

/* startup memory settings [Associated for constant and dynamic mode.] */
#define STARTUP_MEMORY_ALLOCATION_BLOCKS          16 // FIRST_RESERVE_AMOUNT

/* Constant overflow management */
// using if: GT_ACTIVATE_AUTOMATIC_MODE_FOR_OVERFLOW == not defined
#define MINIMAL_OVERFLOW_FOR_CONSTANT_MODE         1 // MINIMAL_OVERFLOW
#define MAXIMAL_OVERFLOW_FOR_CONSTANT_MODE      5000 // MAXIMAL_OVERFLOW
#define REMOVE_IF_IT_IS_LARGER_FOR_CONSTANT_MODE  50 // REMOVE_IF_IT_IS_LARGER

/* Dynamic overflow management */
// using if: GT_ACTIVATE_AUTOMATIC_MODE_FOR_OVERFLOW == are defined
#define AUTO_MINIMAL_OVERFLOW_FOR_DYNAMIC_MODE     0 // AUTO_MINIMAL_OVERFLOW
#define AUTO_MAXIMAL_OVERFLOW_FOR_DYNAMIC_MODE    26 // AUTO_MAXIMAL_OVERFLOW
#define ADJUST_BASE_NUMBER_FOR_DYNAMIC_MODE        1 // ADJUST_BASE_NUMBER
#define INITIAL_BASE_VALUE_FOR_DYNAMIC_MODE        4 // INITIAL_BASE_VALUE
// -------------------------------------MEMORY-SETTINGS-END------------------------------------- //



// --------------------------------------------------------------------------------------------- //
// - - - - - - - - - - - - - - - - - - - - DO NOT TOUCH! - - - - - - - - - - - - - - - - - - - - //
// - - - - - - - - - - - - - - FROM THIS LINE CHANGES ARE PROHIBITED - - - - - - - - - - - - - - //
// --------------------------------------------------------------------------------------------- //

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <algorithm>

/** Memory allocation:
 *		Implementation of GT::ALLOCATE to substitute the "new" operator.
 *		The GT_ALLOCATER_T is a Place-Marker of GT::ALLOCATE
*/
#define GT_ALLOCATER_T new

namespace GT
{
	#if !defined(IMALLOC_H)
	#if !defined(GTHEADER_H)
	const class null_ptr_t // Implementation of null_ptr
	{
		public:
			template<class T> operator T*() const{return 0;}
			template<class C, class T> operator T C::*() const{return 0;}
		private:
			void operator&() const;
	} null_ptr = {};

	template<class T> bool operator==(T *t, null_ptr_t)
	{
		return (t == static_cast<T*>(null_ptr));
	}

	template<class T> bool operator==(null_ptr_t, T *t)
	{
		return (t == static_cast<T*>(null_ptr));
	}
	template<class T> bool operator!=(T *t, null_ptr_t)
	{
		return (t != static_cast<T*>(null_ptr));
	}

	template<class T> bool operator!=(null_ptr_t, T *t)
	{
		return (t != static_cast<T*>(null_ptr));
	}
	#endif // GTHEADER_H
	#endif // IMALLOC_H

	/* Class: reverse_iterator_t<T>:
		The class reverse_iterator_t handle the reverse
		iteration steps about const and not const objects.
	*/
	template<class Base> class reverse_iterator_t
	{
		private:
			typedef reverse_iterator_t<Base> self_type;
			typedef const self_type self_tp_c;
			typedef Base *pointer_t;
			typedef Base &reference;
			typedef const Base BaseConst;
			typedef bool boolean_t;
			mutable pointer_t ptr;

		public:
			reverse_iterator_t(pointer_t p = null_ptr): ptr(p){}
			reverse_iterator_t(const self_type &src): ptr(src.ptr){}

			inline reference operator*(void);
			inline self_type operator++(int);
			inline pointer_t operator->(void);
			inline self_type operator++(void);
			inline self_type operator++(void) const;
			inline self_type operator++(int) const;
			inline BaseConst operator*(void) const;
			inline self_tp_c operator=(const self_type &src) const;
			inline boolean_t operator==(const self_type &rhs) const;
			inline boolean_t operator!=(const self_type &rhs) const;
			inline self_type operator=(const pointer_t src)
			{
				this->ptr = src; return *this;
			}

			inline self_type operator=(const self_type &src)
			{
				this->ptr = src.ptr; return *this;
			}

			inline self_tp_c operator=(const pointer_t src) const
			{
				this->ptr = src; return *this;
			}
	};

	template<class Base>
	Base &reverse_iterator_t<Base>::operator*(void)
	{
		return *this->ptr;
	}

	template<class Base>
	Base *reverse_iterator_t<Base>::operator->(void)
	{
		return this->ptr;
	}

	template<class Base>
	const Base reverse_iterator_t<Base>::operator*(void) const
	{
		return *this->ptr;
	}

	template<class Base>
	reverse_iterator_t<Base> reverse_iterator_t<Base>::operator++(int)
	{
		this->ptr--; return *this;
	}

	template<class Base>
	reverse_iterator_t<Base> reverse_iterator_t<Base>::operator++(int) const
	{
		this->ptr--; return *this;
	}

	template<class Base>
	reverse_iterator_t<Base> reverse_iterator_t<Base>::operator++(void)
	{
		reverse_iterator_t<Base> i = *this; ptr--; return i;
	}

	template<class Base>
	reverse_iterator_t<Base> reverse_iterator_t<Base>::operator++(void) const
	{
		reverse_iterator_t<Base> i = *this; ptr--; return i;
	}

	template<class Base>
	bool reverse_iterator_t<Base>::operator==(const reverse_iterator_t<Base> &rhs) const
	{
		return this->ptr == rhs.ptr;
	}

	template<class Base>
	bool reverse_iterator_t<Base>::operator!=(const reverse_iterator_t<Base> &rhs) const
	{
		return this->ptr != rhs.ptr;
	}

	template<class Base>
	const reverse_iterator_t<Base> reverse_iterator_t<Base>::operator=(const reverse_iterator_t<Base> &src) const
	{
		this->ptr = src.ptr; return *this;
	}

	/* Struct: Husk:
		The struct Husk it's a summary of important components.
	*/
	template<class T> struct Husk
	{
		// Attributes
			T ascending;			// highly number from base
			T bearingsCount;		// ceases to increase by limit
			T actualSize;			// actual size of elements
			T actualCapacity;		// actual alocated memory

		// Methods
			inline explicit Husk<T>(T ascending, T bearingsCount, T actualSize, T actualCapacity):
				ascending(ascending), bearingsCount(bearingsCount),
				actualSize(actualSize), actualCapacity(actualCapacity){}

			inline Husk<T>(const Husk<T> &get):
				ascending(get.ascending), bearingsCount(get.bearingsCount),
				actualSize(get.actualSize), actualCapacity(get.actualCapacity){}

			inline void setHusk(T a, T b, T c, T d);
			inline Husk<T> operator=(const Husk<T> &src);
	}; typedef GT::Husk<size_t> husk_t;
	template<class T> void GT::Husk<T>::setHusk(T a, T b, T c, T d)
	{	// 1. ascending   2. bearingsCount   3. actualSize   4. actualCapacity
		this->actualSize = c; this->bearingsCount = b; this->ascending = a; this->actualCapacity = d;
	}
	template<class T> Husk<T> GT::Husk<T>::operator=(const Husk<T> &src)
	{
		this->ascending = src.ascending;
		this->bearingsCount = src.bearingsCount;
		this->actualSize = src.actualSize;
		this->actualCapacity = src.actualCapacity;
		return *this;
	}

	#if !defined(GTHEADER_H)
	/* to check whether a class is derived from each other class. */
	template<class Base, class Derived> class is
	{
		private:
			struct yes{char _yes;};
			struct no{char _n[2];};

			static yes test_derived(Base);
			static no test_derived(...);

		public:
			static const bool derived = sizeof(test_derived(Derived())) == sizeof(yes);
	};
	#endif // GTHEADER_H

	template<class T> class iVector
	{
		private:
		// Attributes
			husk_t core;	// important attributes, see class Husk
			T *objects;		// generic pointer for the dynamic array

			enum // Startup memory settings
			{
				FIRST_RESERVE_AMOUNT	= STARTUP_MEMORY_ALLOCATION_BLOCKS
			};

			/* Constant overflow management */
			enum // using if: GT_ACTIVATE_AUTOMATIC_MODE_FOR_OVERFLOW == not defined
			{
				MINIMAL_OVERFLOW		= MINIMAL_OVERFLOW_FOR_CONSTANT_MODE,
				MAXIMAL_OVERFLOW		= MAXIMAL_OVERFLOW_FOR_CONSTANT_MODE,
				REMOVE_IF_IT_IS_LARGER	= REMOVE_IF_IT_IS_LARGER_FOR_CONSTANT_MODE
			};

			/* Dynamic overflow management */
			enum // using if: GT_ACTIVATE_AUTOMATIC_MODE_FOR_OVERFLOW == are defined
			{
				AUTO_MINIMAL_OVERFLOW	= AUTO_MINIMAL_OVERFLOW_FOR_DYNAMIC_MODE,
				AUTO_MAXIMAL_OVERFLOW	= AUTO_MAXIMAL_OVERFLOW_FOR_DYNAMIC_MODE,
				ADJUST_BASE_NUMBER		= ADJUST_BASE_NUMBER_FOR_DYNAMIC_MODE,
				INITIAL_BASE_VALUE		= INITIAL_BASE_VALUE_FOR_DYNAMIC_MODE
			};


		// Private methods

			/* Using the bitshift left operator to calc the new overflow for ascending */
			inline size_t shift_left(void);

			/* Using the bitshift operator right to calc the new overflow for ascending */
			inline size_t shift_right(void);

			/* Delete an element using the index */
			inline void kill_item(const size_t index);

			/* Set new core settings */
			inline void setCore(const husk_t &src);


		public:

		// Iterator types
			typedef T *iterator;
			typedef const T *const_iterator;
			typedef reverse_iterator_t<T> reverse_iterator;
			typedef const reverse_iterator_t<T> const_reverse_iterator;


		// Constructors

			/* Creates a iVector of length n, containing n copies of the default value for type T.
			 * Requires that constructor have a number. */
			inline explicit iVector(const size_t initCapacity = 0):
				// 1. ascending   2. bearingsCount   3. actualSize   4. actualCapacity
				core(INITIAL_BASE_VALUE, 0, 0, initCapacity > ((FIRST_RESERVE_AMOUNT < 1) ?
																   1 : FIRST_RESERVE_AMOUNT) ?
						 initCapacity : ((FIRST_RESERVE_AMOUNT < 1) ? 1 : FIRST_RESERVE_AMOUNT)),
				objects(GT_ALLOCATER_T T[this->core.actualCapacity != 0 ? this->core.actualCapacity : 1]){}

			/* Creates a iVector of length n, containing n copies of value. */
			inline explicit iVector(const T &src, const size_t size = 1):
				core(INITIAL_BASE_VALUE, 0, size, (FIRST_RESERVE_AMOUNT < size) ? (size + 1) : FIRST_RESERVE_AMOUNT),
				objects(GT_ALLOCATER_T T[(FIRST_RESERVE_AMOUNT < size) ? (size + 1) : FIRST_RESERVE_AMOUNT])
			{	// 1. ascending   2. bearingsCount   3. actualSize   4. actualCapacity
				for(size_t i=0; i<size; i++) this->operator[](i) = src;
			}

			/* The copy ctor Creates a copy of src. */
			inline iVector(const iVector<T> &src): core(src.getCore())
			{
				this->core.actualSize = 0;
				this->objects = GT_ALLOCATER_T T[src.capacity()];
				iterator i = this->begin();
				for(const_iterator it = src.begin(); it != src.end(); it++, i++) *i = *it;
				this->setCore(src.getCore());
			}

			/* Ctor to convert and creates a copy of src. */
			template<class Y> inline iVector(const iVector<Y> &src): core(src.getCore())
			{
				this->core.actualSize = 0;
				if(is<T, Y>::derived) // Check if Y is a derivation of T
				{
					this->objects = GT_ALLOCATER_T T[src.capacity()];
					iterator i = this->begin();
					for(const Y *it = src.begin(); it != src.end(); it++, i++) *i = *it;
					this->setCore(src.getCore());
				}
				else
				{
					std::cerr << "IN FUNCTION: template<class Y> inline iVector(const iVector<Y> &src);" << std::endl;
					std::cerr << "is<T, Y>::derived == false -> DATATYPE IS NOT COMPATIBLE!" << std::endl;
					this->core.setHusk(INITIAL_BASE_VALUE, 0, 0, (FIRST_RESERVE_AMOUNT < 1) ? 1 : FIRST_RESERVE_AMOUNT);
					this->objects = GT_ALLOCATER_T T[this->core.actualCapacity != 0 ? this->core.actualCapacity : 1];
				}
			}


		// Destructor
			~iVector();


		// Methods

			/* Sorts the elements in the range [first,last) into ascending order.
			 * The elements are compared using operator< for the first version, and comp for the second.
			 * Equivalent elements are not guaranteed to keep their original relative order (see stable_sort). */
			inline void sort(void){std::sort(this->begin(), this->end());}

			/* Using this->sort() and mirror method. */
			inline void sort_reverse(void){this->sort(); this->mirror();}

			/* return clone of this object */
			inline iVector<T> *clone(void){return GT_ALLOCATER_T iVector<T>(*this);}

			/* Replaces elements in *this with n copies of t. The function invalidates all
			 * iterators and references to elements in *this. */
			inline void assign(const iVector<T> &src);

			/* Returns a constant reference to the first element. */
			inline const T &front(void) const;

			/* Returns a reference to the first element. */
			inline T &front(void);

			/* Inserts a copy of x to the begin of self. */
			inline void push_front(const T &x);

			/* Inserts copies of the elements in the range [start, finish) before position. */
			inline void insert(const T new_item, const size_t position = 0);

			/* Deletes the iVector element from the index position begin and deletes any desired number of items. */
			inline void erase(const size_t begin, const size_t pieces = 1);
			inline void erase(const_iterator it, const size_t pieces = 1)
			{
				if(pieces > 0)
					if(this->size() != 0)
					{
						iterator t = GT_ALLOCATER_T T[
								this->capacity() > 1 ? (this->capacity() - 1) > 1 ? this->capacity() - 1 : 1 : 1], temp = t;
						for(const_iterator i = this->begin(); i != this->end(); i++, t++)
							if(i != it) *t = *i; else {t--; (i + pieces - 1) > this->end() ? i = this->end() : i += pieces - 1;}

						this->core.setHusk(this->core.ascending, this->core.bearingsCount,
										   (this->size() - pieces) < 1 ? 1 : this->size() - pieces,
										   this->capacity() > 1 ? (this->capacity() - 1) > 1 ? this->capacity() - 1 : 1 : 1);
						delete[] this->objects;
						this->objects = temp;
					}
			}

			/* Alters the size of self. If the new size (sz) is greater than the current size,
			 * then sz-size() instances of the default value of type T are inserted at the end of the iVector.
			 * If the new size is smaller than the current capacity, then the iVector is truncated by erasing
			 * size()-sz elements off the end. If sz is equal to capacity then no action is taken. */
			inline void resize(const size_t newSize);

			/* Increases the capacity of self in anticipation of adding new elements.
			 * reserve itself does not add any new elements. After a call to reserve,
			 * capacity() is greater than or equal to n and subsequent insertions will
			 * not cause a reallocation until the size of the iVector exceeds n. Reallocation
			 * does not occur if n is less than capacity(). If reallocation does occur,
			 * then all iterators and references pointing to elements in the iVector are invalidated.
			 * reserve takes at most linear time in the size of self. reserve throws a length_error
			 * exception if n is greater than max_size(). */
			inline void reserve(const size_t newCapacity);

			/* Returns true if the size is zero. */
			inline bool empty(void) const;

			/* Returns the number of elements. */
			inline size_t size(void) const;

			/* Returns the size of the allocated storage, as the number of elements that can be stored. */
			inline size_t capacity(void) const;

			/* Inserts a copy of x to the end of self. */
			inline void push_back(const T &x);

			/* Removes the first element of self. */
			inline void pop_front(void);

			/* Removes the last element of self. */
			inline void pop_back(void);

			/* Returns a reference to the last element. */
			inline T &back(void);

			/* Returns a constant reference to the last element. */
			inline const T &back(void) const;

			/* Returns a reference to element n of self. The result can be used as an lvalue.
			 * The index n must be between 0 and the size less one. */
			inline T &at(const size_t index);

			/* Returns a constant reference to element n of self.
			 * The index n must be between 0 and the size less one. */
			inline const T &at(const size_t index) const;

			/* Deletes all elements from the iVector. */
			inline void clear(void);

			/* Exchanges self with src, by swapping all elements. */
			inline void swap(iVector<T> &src);

			/* Return actual core */
			inline husk_t getCore(void) const;

			/* Changes the Direction of all elements. */
			inline void mirror(void);


		// Operators

			/* Caution: Note the size of the datatypes! */
			/* First check if Y are a derivation of T. Is the datatype correct cast the iVector obj in the basic Y* datatype */
			template<class Y> inline operator Y*() const
			{
				if(is<T, Y>::derived) // Check if Y is a derivation of T
					return (Y *)(this->objects);
				else
				{
					std::cerr << "IN FUNCTION: template<class Y> inline operator Y*() const;" << std::endl;
					std::cerr << "is<T, Y>::derived == false -> DATATYPE IS NOT COMPATIBLE!" << std::endl;
					return null_ptr;
				}
			}

			/* cast the iVector obj in the basic T* datatype */
			inline operator T*() const
			{
				return this->objects;
			}

			/* The assignment operator erases all elements in self then inserts into self a copy of each
			 * element in x. Returns a reference to self. */
			inline iVector<T> &operator=(const iVector<T> &rhs);

			/* See push_back */
			inline iVector<T> &operator+=(T &rhs)
			{
				this->push_back(rhs);
				return *this;
			}

			/* First check if Y are a derivation of T. Is the datatype correct make copy of rhs */
			template<class Y> inline iVector<T> &operator=(iVector<Y> &rhs)
			{
				if(is<T, Y>::derived) // Check if Y is a derivation of T
				{
					delete[] this->objects;
					this->setCore(rhs.getCore());
					this->core.actualSize = 0;
					this->objects = GT_ALLOCATER_T T[rhs.capacity()];
					iterator i = this->begin();
					for(const Y *it = rhs.begin(); it != rhs.end(); it++, i++) *i = *it;
					this->setCore(rhs.getCore());
				}
				else
				{
					std::cerr << "IN FUNCTION: template<class Y> inline iVector<T> &operator=(iVector<Y> &rhs);" << std::endl;
					std::cerr << "is<T, Y>::derived == false -> DATATYPE IS NOT COMPATIBLE!" << std::endl;
				}
				return *this;
			}

			/* Returns a reference to element n of self. The result can be used as an lvalue.
			 * The index n must be between 0 and the size less one. */
			inline T &operator[](const size_t index);

			/* Returns a constant reference to element n of self.
			 * The index n must be between 0 and the size less one. */
			inline const T &operator[](const size_t index) const;


		// Iterators

			/* Returns a random access const_reverse_iterator that points to the past-the-end value. */
			inline const_reverse_iterator rbegin(void) const{return &this->operator[](this->size() - 1);}

			/* Returns a random access const_reverse_iterator that points to the first element. */
			inline const_reverse_iterator rend(void) const
			{
				const_reverse_iterator src(&(*(this->objects - 1)));
				return src;
			}

			/* Returns a random access iterator that points to the first element. */
			inline iterator begin(void){return &this->operator[](0);}

			/* Returns a random access const_iterator that points to the first element. */
			inline const_iterator begin(void) const{return &this->operator[](0);}

			/* Returns a random access iterator that points to the past-the-end value. */
			inline iterator end(void){return &this->operator[](this->size());}

			/* Returns a random access const_iterator that points to the past-the-end value. */
			inline const_iterator end(void) const{return &this->operator[](this->size());}

			/* Returns a random access reverse_iterator that points to the past-the-end value. */
			inline reverse_iterator rbegin(void)
			{
				reverse_iterator src(&(*(this->objects + this->size() - 1)));
				return src;
			}

			/* Returns a random access reverse_iterator that points to the first element. */
			inline reverse_iterator rend(void)
			{
				reverse_iterator src(&(*(this->objects - 1)));
				return src;
			}
	};

	template<class T> iVector<T>::~iVector()
	{
		delete[] this->objects;
	}

	template<class T> size_t iVector<T>::shift_left(void)
	{
		if(this->core.bearingsCount < AUTO_MAXIMAL_OVERFLOW)
			return ADJUST_BASE_NUMBER << (this->core.bearingsCount = this->core.ascending++);
		else return ADJUST_BASE_NUMBER << this->core.bearingsCount;
	}

	template<class T> size_t iVector<T>::shift_right(void)
	{
		this->core.bearingsCount = --this->core.ascending;
		return this->core.actualCapacity >> ADJUST_BASE_NUMBER;
	}

	template<class T> iVector<T> &iVector<T>::operator=(const iVector<T> &rhs)
	{
		if(this != &rhs)
		{
			delete[] this->objects;
			this->core.operator=(rhs.getCore());
			this->objects = GT_ALLOCATER_T T[this->capacity()];
			iterator i = this->begin();
			for(const_iterator it = rhs.begin(); it != rhs.end(); it++, i++) *i = *it;
		}
		return *this;
	}

	template<class T> void iVector<T>::clear(void)
	{
		delete[] this->objects;
		this->core.setHusk(0, 0, 0, (FIRST_RESERVE_AMOUNT < 1) ? 1 : FIRST_RESERVE_AMOUNT);
		this->objects = GT_ALLOCATER_T T[(FIRST_RESERVE_AMOUNT < 1) ? 1 : FIRST_RESERVE_AMOUNT];
		if(this->objects == null_ptr)
		{	// 1. ascending   2. bearingsCount   3. actualSize   4. actualCapacity
			std::cerr << "IN FUNCTION: template<class T> void iVector<T>::clear(void);" << std::endl;
			std::cerr << "NOT ENOUGHT MEMORY." << std::endl;
			return;
		}
	}

	template<class T> void iVector<T>::resize(const size_t newSize)
	{
		if(newSize > this->core.actualCapacity)
			this->reserve(newSize * 2 + 1);
		this->core.actualSize = newSize;
	}

	template<class T> void iVector<T>::reserve(const size_t newCapacity)
	{
		if(newCapacity < this->core.actualSize) return;
		T *oldArray = this->objects;

		this->objects = GT_ALLOCATER_T T[newCapacity];
		if(this->objects == null_ptr)
		{
			std::cerr << "IN FUNCTION: template<class T> void iVector<T>::reserve(const size_t newCapacity);" << std::endl;
			std::cerr << "NOT ENOUGHT MEMORY." << std::endl;
		}
		else
		{
			for(size_t i=0; i<this->core.actualSize; i++) this->objects[i] = oldArray[i];
			this->core.actualCapacity = newCapacity;
			delete[] oldArray;
		}
	}

	template<class T> void iVector<T>::insert(const T new_item, const size_t position)
	{
		iVector<T> temp;
		if(temp.capacity() < (this->size() + 1)) temp.reserve(this->size() + 1);
		position = position > (this->size()) ? (this->size()) : position;
		for(size_t i=0, j=0; i<this->size()+1; i++, j++)
		{
			if(i != position) temp.push_back(this->operator[](j));
			else
			{
				temp.push_back(new_item);
				j--;
			}
		}
		this->operator=(temp);
	}

	template<class T> void iVector<T>::swap(iVector<T> &src)
	{
		if(this->objects != src.objects)
		{
			T *tmpArray = this->objects;
			husk_t tmp(this->getCore());
			this->setCore(src.getCore());
			src.setCore(tmp);
			this->objects = src.objects;
			src.objects = tmpArray;
		}
	}

	template<class T> void iVector<T>::mirror(void)
	{
		if(!this->empty())
		{
			iterator i = GT_ALLOCATER_T T[this->core.actualCapacity], temp = i;
			for(reverse_iterator r = this->rbegin(); r != this->rend(); r++, i++) *i = *r;
			delete[] this->objects;
			this->objects = temp;
		}
	}

	template<class T> void iVector<T>::setCore(const husk_t &src)
	{
		this->core = src;
	}

	template<class T> void iVector<T>::kill_item(const size_t index)
	{
		iVector<T> temp;
		for(size_t i=0; i<this->size(); i++)
			if(i != index) temp.push_back(this->operator[](i));
		this->operator=(temp);
	}

	template<class T> void iVector<T>::assign(const iVector<T> &src)
	{
		this->operator=(src);
	}

	template<class T> T &iVector<T>::front(void)
	{
		return this->operator[](0);
	}

	template<class T> const T &iVector<T>::front(void) const
	{
		return this->operator[](0);
	}

	template<class T> void iVector<T>::erase(const size_t begin, const size_t pieces)
	{
		//		iVector<T>::const_iterator iter = &this->operator[](begin);
		//		this->erase(iter, pieces);
		for(size_t i=0; i<pieces; i++) this->kill_item(begin);
	}

	template<class T> T &iVector<T>::operator[](const size_t index)
	{
		return this->objects[index];
	}

	template<class T> const T &iVector<T>::operator[](const size_t index) const
	{
		return this->objects[index];
	}

	template<class T> bool iVector<T>::empty(void) const
	{
		return bool(this->size() == 0);
	}

	template<class T> size_t iVector<T>::size(void) const
	{
		return this->core.actualSize;
	}

	template<class T> size_t iVector<T>::capacity(void) const
	{
		return this->core.actualCapacity;
	}

	template<class T> husk_t iVector<T>::getCore(void) const
	{
		return this->core;
	}

	template<class T> void iVector<T>::pop_front(void)
	{
		this->erase(this->begin());
	}

	template<class T> void iVector<T>::push_front(const T &x)
	{
		iVector<T> tmp(x, 1);
		for(iterator i=this->begin(); i!=this->end(); i++) tmp.push_back(*i);
		this->operator=(tmp);
	}

	template<class T> void iVector<T>::push_back(const T &x)
	{
	#if defined(GT_ACTIVATE_AUTOMATIC_MODE_FOR_OVERFLOW)
		if(this->core.actualSize == (this->core.actualCapacity - AUTO_MINIMAL_OVERFLOW))
			this->reserve(this->core.actualCapacity + this->shift_left());
		this->objects[this->core.actualSize++] = x;
	#else
		if(MAXIMAL_OVERFLOW == 0)
		{
			if(this->core.actualSize == (this->core.actualCapacity - MINIMAL_OVERFLOW))
				this->reserve(this->core.actualCapacity + 1);
			this->objects[this->core.actualSize++] = x;
		}
		else
		{
			if(this->core.actualSize == (this->core.actualCapacity - MINIMAL_OVERFLOW))
				this->reserve(this->core.actualCapacity + MAXIMAL_OVERFLOW);
			this->objects[this->core.actualSize++] = x;
		}
	#endif // GT_ACTIVATE_AUTOMATIC_MODE_FOR_OVERFLOW
	}

	template<class T> void iVector<T>::pop_back(void)
	{
	#if defined(GT_ACTIVATE_AUTOMATIC_MODE_FOR_OVERFLOW)
		if((this->core.actualCapacity - this->core.actualSize-- + 1) > this->shift_right())
		{
			const T *oldArray = this->objects;

			this->objects = GT_ALLOCATER_T T[this->core.actualSize + 1];
			for(size_t i=0; i<this->core.actualSize; i++)
				this->objects[i] = oldArray[i];
			this->core.actualCapacity = this->core.actualSize + 1;
			delete[] oldArray;
		}
	#else
		if((this->core.actualCapacity - this->core.actualSize--) > REMOVE_IF_IT_IS_LARGER)
		{
			T *oldArray = this->objects;

			this->objects = GT_ALLOCATER_T T[this->core.actualSize + 1];
			for(size_t i=0; i<core.actualSize; i++)
				this->objects[i] = oldArray[i];
			this->core.actualCapacity = this->core.actualSize + 1;
			delete[] oldArray;
		}
	#endif // GT_ACTIVATE_AUTOMATIC_MODE_FOR_OVERFLOW
	}

	template<class T> T &iVector<T>::at(const size_t index)
	{
		if(index >= this->core.actualSize)
		{
			if(this->core.actualSize != 0)
			{
				std::cerr << "IN FUNCTION: template<class T> T &iVector<T>::at(size_t index);" << std::endl;
				std::cerr << "Caution: The largest possible index of the \"at()\" function is " << this->core.actualSize - 1
						  << " and you have entered the number " << index << " !!!" << std::endl;
				return this->operator[](this->core.actualSize - 1);
			}
			else
			{
				return this->operator[](this->core.actualSize);
			}
		}
		else return this->operator[](index);
	}

	template<class T> const T &iVector<T>::at(const size_t index) const
	{
		if(index >= this->core.actualSize)
		{
			if(this->core.actualSize != 0)
			{
				std::cerr << "IN FUNCTION: template<class T> const T &iVector<T>::at(size_t index) const;" << std::endl;
				std::cerr << "Caution: The largest possible index of the \"at()\" function is " << this->core.actualSize - 1
						  << " and you have entered the number " << index << " !!!" << std::endl;
				return this->back();
			}
			else
			{
				return this->front();
			}
		}
		else return *(this->objects + index - 1);
	}

	template<class T> const T &iVector<T>::back(void) const
	{
		return this->operator[](this->core.actualSize - 1);
	}
} // end of namespace GT
#endif // IVECTOR_H
