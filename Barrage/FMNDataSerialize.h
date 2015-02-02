/************************************************************************/
/*	Copyright (c) 2015 FMN. All rights reserved.                        */
/************************************************************************/
#pragma once
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_wiarchive.hpp>
#include <boost/archive/xml_woarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>


#ifdef _DEBUG
#pragma comment(lib, "libboost_serialization-vc120-mt-gd-1_57.lib")
#else
#pragma comment(lib, "libboost_serialization-vc120-mt-1_57.lib")
#endif


#define FMN_SERIALIZE_BEGIN                                                      \
    friend class boost::serialization::access;                                  \
    template<class Archive>                                                     \
    void serialize(Archive & ar, const unsigned int /*version*/)                \
    {


#define FMN_SERIALIZE_END                                                        \
    }


#define FMN_SERIALIZE_1(p1)                                                      \
    FMN_SERIALIZE_BEGIN                                                          \
    ar & p1;                                                                    \
    FMN_SERIALIZE_END


#define FMN_SERIALIZE_2(p1, p2)                                                  \
    FMN_SERIALIZE_BEGIN                                                          \
    ar & p1;                                                                    \
    ar & p2;                                                                    \
    FMN_SERIALIZE_END


#define FMN_SERIALIZE_3(p1, p2, p3)                                              \
    FMN_SERIALIZE_BEGIN                                                          \
    ar & p1;                                                                    \
    ar & p2;                                                                    \
    ar & p3;                                                                    \
    FMN_SERIALIZE_END


#define FMN_SERIALIZE_4(p1, p2, p3, p4)                                          \
    FMN_SERIALIZE_BEGIN                                                          \
    ar & p1;                                                                    \
    ar & p2;                                                                    \
    ar & p3;                                                                    \
    ar & p4;                                                                    \
    FMN_SERIALIZE_END


#define FMN_SERIALIZE_5(p1, p2, p3, p4, p5)                                      \
    FMN_SERIALIZE_BEGIN                                                          \
    ar & p1;                                                                    \
    ar & p2;                                                                    \
    ar & p3;                                                                    \
    ar & p4;                                                                    \
    ar & p5;                                                                    \
    FMN_SERIALIZE_END


#define FMN_SERIALIZE_6(p1, p2, p3, p4, p5, p6)                                 \
    FMN_SERIALIZE_BEGIN                                                         \
    ar & p1;                                                                    \
    ar & p2;                                                                    \
    ar & p3;                                                                    \
    ar & p4;                                                                    \
    ar & p5;                                                                    \
    ar & p6;                                                                    \
    FMN_SERIALIZE_END


#define FMN_SERIALIZE_NVP_6(p1, p2, p3, p4, p5, p6)                             \
    FMN_SERIALIZE_BEGIN                                                         \
    ar & BOOST_SERIALIZATION_NVP(p1);                                           \
    ar & BOOST_SERIALIZATION_NVP(p2);                                           \
    ar & BOOST_SERIALIZATION_NVP(p3);                                           \
    ar & BOOST_SERIALIZATION_NVP(p4);                                           \
    ar & BOOST_SERIALIZATION_NVP(p5);                                           \
    ar & BOOST_SERIALIZATION_NVP(p6);                                           \
    FMN_SERIALIZE_END


#define FMN_SERIALIZE_6(p1, p2, p3, p4, p5, p6)                                  \
    FMN_SERIALIZE_BEGIN                                                          \
    ar & p1;                                                                    \
    ar & p2;                                                                    \
    ar & p3;                                                                    \
    ar & p4;                                                                    \
    ar & p5;                                                                    \
    ar & p6;                                                                    \
    FMN_SERIALIZE_END


#define FMN_SERIALIZE_7(p1, p2, p3, p4, p5, p6, p7)                              \
    FMN_SERIALIZE_BEGIN                                                          \
    ar & p1;                                                                    \
    ar & p2;                                                                    \
    ar & p3;                                                                    \
    ar & p4;                                                                    \
    ar & p5;                                                                    \
    ar & p6;                                                                    \
    ar & p7;                                                                    \
    FMN_SERIALIZE_END


#define FMN_SERIALIZE_NVP_7(p1, p2, p3, p4, p5, p6, p7)                         \
    FMN_SERIALIZE_BEGIN                                                         \
    ar & BOOST_SERIALIZATION_NVP(p1);                                           \
    ar & BOOST_SERIALIZATION_NVP(p2);                                           \
    ar & BOOST_SERIALIZATION_NVP(p3);                                           \
    ar & BOOST_SERIALIZATION_NVP(p4);                                           \
    ar & BOOST_SERIALIZATION_NVP(p5);                                           \
    ar & BOOST_SERIALIZATION_NVP(p6);                                           \
    ar & BOOST_SERIALIZATION_NVP(p7);                                           \
    FMN_SERIALIZE_END


#define FMN_SERIALIZE_8(p1, p2, p3, p4, p5, p6, p7, p8)                          \
    FMN_SERIALIZE_BEGIN                                                          \
    ar & p1;                                                                    \
    ar & p2;                                                                    \
    ar & p3;                                                                    \
    ar & p4;                                                                    \
    ar & p5;                                                                    \
    ar & p6;                                                                    \
    ar & p7;                                                                    \
    ar & p8;                                                                    \
    FMN_SERIALIZE_END


#define FMN_SERIALIZE_NVP_8(p1, p2, p3, p4, p5, p6, p7, p8)                     \
    FMN_SERIALIZE_BEGIN                                                         \
    ar & BOOST_SERIALIZATION_NVP(p1);                                           \
    ar & BOOST_SERIALIZATION_NVP(p2);                                           \
    ar & BOOST_SERIALIZATION_NVP(p3);                                           \
    ar & BOOST_SERIALIZATION_NVP(p4);                                           \
    ar & BOOST_SERIALIZATION_NVP(p5);                                           \
    ar & BOOST_SERIALIZATION_NVP(p6);                                           \
    ar & BOOST_SERIALIZATION_NVP(p7);                                           \
    ar & BOOST_SERIALIZATION_NVP(p8);                                           \
    FMN_SERIALIZE_END


#define FMN_SERIALIZE_9(p1, p2, p3, p4, p5, p6, p7, p8, p9)                      \
    FMN_SERIALIZE_BEGIN                                                          \
    ar & p1;                                                                    \
    ar & p2;                                                                    \
    ar & p3;                                                                    \
    ar & p4;                                                                    \
    ar & p5;                                                                    \
    ar & p6;                                                                    \
    ar & p7;                                                                    \
    ar & p8;                                                                    \
    ar & p9;                                                                    \
    FMN_SERIALIZE_END

