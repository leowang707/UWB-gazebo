// Generated by gencpp from file gtec_msgs/RadarRangeDoppler.msg
// DO NOT EDIT!


#ifndef GTEC_MSGS_MESSAGE_RADARRANGEDOPPLER_H
#define GTEC_MSGS_MESSAGE_RADARRANGEDOPPLER_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace gtec_msgs
{
template <class ContainerAllocator>
struct RadarRangeDoppler_
{
  typedef RadarRangeDoppler_<ContainerAllocator> Type;

  RadarRangeDoppler_()
    : header()
    , numRangeBins(0)
    , numDopplerBins(0)
    , data()  {
    }
  RadarRangeDoppler_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , numRangeBins(0)
    , numDopplerBins(0)
    , data(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef int16_t _numRangeBins_type;
  _numRangeBins_type numRangeBins;

   typedef int16_t _numDopplerBins_type;
  _numDopplerBins_type numDopplerBins;

   typedef std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> _data_type;
  _data_type data;





  typedef boost::shared_ptr< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> const> ConstPtr;

}; // struct RadarRangeDoppler_

typedef ::gtec_msgs::RadarRangeDoppler_<std::allocator<void> > RadarRangeDoppler;

typedef boost::shared_ptr< ::gtec_msgs::RadarRangeDoppler > RadarRangeDopplerPtr;
typedef boost::shared_ptr< ::gtec_msgs::RadarRangeDoppler const> RadarRangeDopplerConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator1> & lhs, const ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.numRangeBins == rhs.numRangeBins &&
    lhs.numDopplerBins == rhs.numDopplerBins &&
    lhs.data == rhs.data;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator1> & lhs, const ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace gtec_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> >
{
  static const char* value()
  {
    return "54bb64bfdc5d84bbb760ced1e7d42afe";
  }

  static const char* value(const ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x54bb64bfdc5d84bbULL;
  static const uint64_t static_value2 = 0xb760ced1e7d42afeULL;
};

template<class ContainerAllocator>
struct DataType< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> >
{
  static const char* value()
  {
    return "gtec_msgs/RadarRangeDoppler";
  }

  static const char* value(const ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"int16 numRangeBins\n"
"int16 numDopplerBins\n"
"float64[] data\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
;
  }

  static const char* value(const ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.numRangeBins);
      stream.next(m.numDopplerBins);
      stream.next(m.data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct RadarRangeDoppler_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::gtec_msgs::RadarRangeDoppler_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "numRangeBins: ";
    Printer<int16_t>::stream(s, indent + "  ", v.numRangeBins);
    s << indent << "numDopplerBins: ";
    Printer<int16_t>::stream(s, indent + "  ", v.numDopplerBins);
    s << indent << "data[]" << std::endl;
    for (size_t i = 0; i < v.data.size(); ++i)
    {
      s << indent << "  data[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.data[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // GTEC_MSGS_MESSAGE_RADARRANGEDOPPLER_H
