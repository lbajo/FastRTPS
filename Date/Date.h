#ifndef _Date_H_
#define _Date_H_

#include <stdint.h>
#include <array>
#include <string>
#include <vector>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif
#else
#define eProsima_user_DllExport
#endif

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(Date_SOURCE)
#define Date_DllAPI __declspec( dllexport )
#else
#define Date_DllAPI __declspec( dllimport )
#endif // Date_SOURCE
#else
#define Date_DllAPI
#endif
#else
#define Date_DllAPI
#endif // _WIN32

namespace eprosima
{
    namespace fastcdr
    {
        class Cdr;
    }
}

/*!
 * @brief This class represents the structure Date defined by the user in the IDL file.
 * @ingroup DATE
 */
class Date
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport Date();
    
    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~Date();
    
    /*!
     * @brief Copy constructor.
     * @param x Reference to the object Date that will be copied.
     */
    eProsima_user_DllExport Date(const Date &x);
    
    /*!
     * @brief Move constructor.
     * @param x Reference to the object Date that will be copied.
     */
    eProsima_user_DllExport Date(Date &&x);
    
    /*!
     * @brief Copy assignment.
     * @param x Reference to the object Date that will be copied.
     */
    eProsima_user_DllExport Date& operator=(const Date &x);
    
    /*!
     * @brief Move assignment.
     * @param x Reference to the object Date that will be copied.
     */
    eProsima_user_DllExport Date& operator=(Date &&x);
    
    /*!
     * @brief This function sets a value in member num
     * @param _num New value for member num
     */
    inline eProsima_user_DllExport void num(uint32_t _num)
    {
        m_num = _num;
    }

    /*!
     * @brief This function returns the value of member num
     * @return Value of member num
     */
    inline eProsima_user_DllExport uint32_t num() const
    {
        return m_num;
    }

    /*!
     * @brief This function returns a reference to member num
     * @return Reference to member num
     */
    inline eProsima_user_DllExport uint32_t& num()
    {
        return m_num;
    }
    /*!
     * @brief This function copies the value in member msg
     * @param _msg New value to be copied in member msg
     */
    inline eProsima_user_DllExport void msg(const std::string &_msg)
    {
        m_msg = _msg;
    }

    /*!
     * @brief This function moves the value in member msg
     * @param _msg New value to be moved in member msg
     */
    inline eProsima_user_DllExport void msg(std::string &&_msg)
    {
        m_msg = std::move(_msg);
    }

    /*!
     * @brief This function returns a constant reference to member msg
     * @return Constant reference to member msg
     */
    inline eProsima_user_DllExport const std::string& msg() const
    {
        return m_msg;
    }

    /*!
     * @brief This function returns a reference to member msg
     * @return Reference to member msg
     */
    inline eProsima_user_DllExport std::string& msg()
    {
        return m_msg;
    }
    
    /*!
     * @brief This function returns the maximum serialized size of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getMaxCdrSerializedSize(size_t current_alignment = 0);

    /*!
     * @brief This function returns the serialized size of a data depending on the buffer alignment.
     * @param data Data which is calculated its serialized size.
     * @param current_alignment Buffer alignment.
     * @return Serialized size.
     */
    eProsima_user_DllExport static size_t getCdrSerializedSize(const Date& data, size_t current_alignment = 0);


    /*!
     * @brief This function serializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serialize(eprosima::fastcdr::Cdr &cdr) const;

    /*!
     * @brief This function deserializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void deserialize(eprosima::fastcdr::Cdr &cdr);



    /*!
     * @brief This function returns the maximum serialized size of the Key of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(size_t current_alignment = 0);

    /*!
     * @brief This function tells you if the Key has been defined for this type
     */
    eProsima_user_DllExport static bool isKeyDefined();

    /*!
     * @brief This function serializes the key members of an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serializeKey(eprosima::fastcdr::Cdr &cdr) const;
    
private:
    uint32_t m_num;
    std::string m_msg;

};

#endif // _Date_H_
