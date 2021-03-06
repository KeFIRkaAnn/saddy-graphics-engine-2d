#pragma warning(push)
#pragma warning(disable: 4273)
#pragma warning(disable: 4351)
#include "object.h"
#include "sadptrhash.h"
#include "sadstring.h"
#include "sprite2d.h"
#define _INC_STDIO
#include "3rdparty/tpunit++/tpunit++.hpp"
#pragma warning(pop)

// Declare primary descendants
class DirectDescendant1: public sad::Object 
{
    SAD_OBJECT
    protected:
        int m_dir_desc_prot1;
    public:
    DirectDescendant1() { m_dir_desc_prot1 = 1;}
    virtual int local1() { return m_dir_desc_prot1;}
};
DECLARE_SOBJ(DirectDescendant1);
class DirectDescendant2: public sad::Object 
{
    SAD_OBJECT
    protected:
        int m_dir_dec_prot2;
    public:
    DirectDescendant2() { 
        m_dir_dec_prot2 = 2;
    }
    virtual int local2() { 
        return m_dir_dec_prot2;
    }
};
DECLARE_SOBJ(DirectDescendant2);
class DirectDescendant3: public sad::Object 
{
    SAD_OBJECT
    protected:
        int m_dir_dec_prot3;
    public:
    DirectDescendant3() { m_dir_dec_prot3 = 3; }
    virtual int local3() { return m_dir_dec_prot3;}
};
DECLARE_SOBJ(DirectDescendant3);
class DirectDescendant4: public sad::Object 
{
    SAD_OBJECT
    protected:
        int m_dir_dec_prot4;
    public:
    DirectDescendant4() { m_dir_dec_prot4 = 4;}
    virtual int local4() { return m_dir_dec_prot4;}

};
DECLARE_SOBJ(DirectDescendant4);

class InheritedFrom1: public DirectDescendant1 {
    SAD_OBJECT
    protected:
        int m_inh_from1;
    public:
    InheritedFrom1() { m_inh_from1 = 5; }
    virtual int local() { return m_inh_from1;}
};

DECLARE_SOBJ_INHERITANCE(InheritedFrom1, 
                         DirectDescendant1);

class InheritedFrom2 : public InheritedFrom1, public DirectDescendant2
{
    SAD_OBJECT
    protected:
        int m_inh_from2;
    public:
    InheritedFrom2() { m_inh_from2 = 6; }
    int local() { return m_inh_from2;}
};

DECLARE_DB_TYPENAME_VIA_EXPLICIT_PARENT(InheritedFrom1, InheritedFrom2)


DECLARE_SOBJ_INHERITANCE2(InheritedFrom2, 
                          InheritedFrom1, 
                          DirectDescendant2);

class InheritedFrom3 : public InheritedFrom1, 
                       public DirectDescendant2,
                       public DirectDescendant3
{
    SAD_OBJECT
    protected:
        int m_inh_from3;
    public:
    InheritedFrom3() { m_inh_from3 = 7; }
    int local() { return m_inh_from3;}
};

DECLARE_DB_TYPENAME_VIA_EXPLICIT_PARENT(InheritedFrom1, InheritedFrom3)

DECLARE_SOBJ_INHERITANCE3(InheritedFrom3, 
                          InheritedFrom1, 
                          DirectDescendant2,
                          DirectDescendant3);

class InheritedFrom4 : public InheritedFrom1, 
                       public DirectDescendant2,
                       public DirectDescendant3,
                       public DirectDescendant4
{
    SAD_OBJECT
    protected:
        int m_inh_from4;
    public:
    InheritedFrom4() { m_inh_from4 = 8;}
    int local() { return m_inh_from4;}
};

DECLARE_DB_TYPENAME_VIA_EXPLICIT_PARENT(InheritedFrom1, InheritedFrom4)


DECLARE_SOBJ_INHERITANCE4(InheritedFrom4, 
                          InheritedFrom1, 
                          DirectDescendant2,
                          DirectDescendant3,
                          DirectDescendant4);

class CarriedObject: public sad::Object
{
SAD_OBJECT
public:
    CarriedObject()
    {
    }
}  _carried_object;

DECLARE_SOBJ_INHERITANCE(CarriedObject, sad::Object);

class CarriedObject2: public sad::Object
{
SAD_OBJECT
public:
    // Padding to make some insertion hacks fail
    int _pad0;
    int _pad1;
    CarriedObject local;

    CarriedObject2()
    {
    }

    CarriedObject * to_new() const
    {
        return &(const_cast<CarriedObject2*>(this)->local);
    }
}  _carried_object2;

DECLARE_SOBJ_INHERITANCE_WITH_CAST(CarriedObject2, sad::Object, CarriedObject, &CarriedObject2::to_new);

/*!
 * Tests object logic
 */
struct SadObjectTest : tpunit::TestFixture
{
 public:
   SadObjectTest() : tpunit::TestFixture(
       BEFORE(SadObjectTest::init),
       TEST(SadObjectTest::testGlobalMetadata),
       TEST(SadObjectTest::testCanDoUpcastToTop),
       TEST(SadObjectTest::testCanDoLocalUpcast),
       TEST(SadObjectTest::testSuccessfullDowncasts),
       TEST(SadObjectTest::testAncestorToChildrenCastFrom),
       TEST(SadObjectTest::testValidCasts),
       TEST(SadObjectTest::testInheritedFrom1),
       TEST(SadObjectTest::testInheritedFrom2),
       TEST(SadObjectTest::testInheritedFrom3),
       TEST(SadObjectTest::testInheritedFrom4),
       TEST(SadObjectTest::testFailCast),
       TEST(SadObjectTest::testCastMethod),
       TEST(SadObjectTest::testName),
       TEST(SadObjectTest::testSprite)
   ) {}
   /*! Cache, which stores objects by class
    */
   sad::PtrHash<sad::String, sad::Object> m_cache;
   /*! Inits a cache with objects
    */
   void init() 
   {
#define CACHE_TUPLE(CLASS)  m_cache.insert( #CLASS, new CLASS () ); 
#define CACHE_TUPLE2(CLASS)  m_cache.insert( #CLASS, (InheritedFrom1*)(new CLASS ()) ); 
       CACHE_TUPLE(DirectDescendant1);
       CACHE_TUPLE(DirectDescendant2);
       CACHE_TUPLE(DirectDescendant3);
       CACHE_TUPLE(DirectDescendant4);
       CACHE_TUPLE(InheritedFrom1);
       CACHE_TUPLE2(InheritedFrom2);
       CACHE_TUPLE2(InheritedFrom3);
       CACHE_TUPLE2(InheritedFrom4);
#undef  CACHE_TUPLE
#undef  CACHE_TUPLE2
   }

   /*! Tests global metadata workaround with name
    */
   void testGlobalMetadata() 
   {
       ASSERT_EQUAL(DirectDescendant1::globalMetaData()->name(),
                    "DirectDescendant1");
       ASSERT_EQUAL(DirectDescendant2::globalMetaData()->name(),
                    "DirectDescendant2");
       ASSERT_EQUAL(DirectDescendant3::globalMetaData()->name(),
                    "DirectDescendant3");
       ASSERT_EQUAL(DirectDescendant4::globalMetaData()->name(),
                    "DirectDescendant4");
       ASSERT_EQUAL(InheritedFrom1::globalMetaData()->name(),
                    "InheritedFrom1");	   
   }

   void testCanDoUpcastToTop()
   {
       ASSERT_TRUE( m_cache["DirectDescendant1"]->
                    metaData()->canBeCastedTo("sad::Object"));
       ASSERT_TRUE( m_cache["DirectDescendant2"]->
                    metaData()->canBeCastedTo("sad::Object"));
       ASSERT_TRUE( m_cache["DirectDescendant3"]->
                    metaData()->canBeCastedTo("sad::Object"));
       ASSERT_TRUE( m_cache["DirectDescendant4"]->
                    metaData()->canBeCastedTo("sad::Object"));
       ASSERT_TRUE( m_cache["InheritedFrom1"]->
                    metaData()->canBeCastedTo("sad::Object"));
       ASSERT_TRUE( m_cache["InheritedFrom2"]->
                    metaData()->canBeCastedTo("sad::Object"));
       ASSERT_TRUE( m_cache["InheritedFrom3"]->
                    metaData()->canBeCastedTo("sad::Object"));
       ASSERT_TRUE( m_cache["InheritedFrom4"]->
                    metaData()->canBeCastedTo("sad::Object"));
       // Non-connected
       ASSERT_FALSE( m_cache["DirectDescendant2"]->
                    metaData()->canBeCastedTo("DirectDescendant1"));
       // Ancestor to child
       ASSERT_FALSE( m_cache["DirectDescendant1"]->
                    metaData()->canBeCastedTo("InheritedFrom1"));
   }

   void testCanDoLocalUpcast()
   {
        ASSERT_TRUE( m_cache["InheritedFrom1"]->
                    metaData()->canBeCastedTo("DirectDescendant1"));
        ASSERT_TRUE( m_cache["InheritedFrom2"]->
                    metaData()->canBeCastedTo("DirectDescendant1"));
        ASSERT_TRUE( m_cache["InheritedFrom3"]->
                    metaData()->canBeCastedTo("DirectDescendant1"));
        ASSERT_TRUE( m_cache["InheritedFrom4"]->
                    metaData()->canBeCastedTo("DirectDescendant1"));
        ASSERT_TRUE( m_cache["InheritedFrom2"]->
                    metaData()->canBeCastedTo("DirectDescendant2"));
        ASSERT_TRUE( m_cache["InheritedFrom3"]->
                    metaData()->canBeCastedTo("DirectDescendant2"));
        ASSERT_TRUE( m_cache["InheritedFrom4"]->
                    metaData()->canBeCastedTo("DirectDescendant2"));
        ASSERT_TRUE( m_cache["InheritedFrom3"]->
                    metaData()->canBeCastedTo("DirectDescendant3"));
        ASSERT_TRUE( m_cache["InheritedFrom4"]->
                    metaData()->canBeCastedTo("DirectDescendant3"));
        ASSERT_TRUE( m_cache["InheritedFrom4"]->
                    metaData()->canBeCastedTo("DirectDescendant4"));
   }

   void testSuccessfullDowncasts()
   {
       ASSERT_TRUE(m_cache["DirectDescendant1"]->
                   metaData()->canBeCastedFrom("InheritedFrom1"));
       ASSERT_TRUE(m_cache["DirectDescendant1"]->
                   metaData()->canBeCastedFrom("InheritedFrom2"));
       ASSERT_TRUE(m_cache["DirectDescendant1"]->
                   metaData()->canBeCastedFrom("InheritedFrom3"));
       ASSERT_TRUE(m_cache["DirectDescendant1"]->
                   metaData()->canBeCastedFrom("InheritedFrom4"));
       ASSERT_TRUE(m_cache["DirectDescendant2"]->
                   metaData()->canBeCastedFrom("InheritedFrom2"));
       ASSERT_TRUE(m_cache["DirectDescendant2"]->
                   metaData()->canBeCastedFrom("InheritedFrom3"));
       ASSERT_TRUE(m_cache["DirectDescendant2"]->
                   metaData()->canBeCastedFrom("InheritedFrom4"));
       ASSERT_TRUE(m_cache["DirectDescendant3"]->
                   metaData()->canBeCastedFrom("InheritedFrom3"));
       ASSERT_TRUE(m_cache["DirectDescendant3"]->
                   metaData()->canBeCastedFrom("InheritedFrom4"));
       ASSERT_TRUE(m_cache["DirectDescendant4"]->
                   metaData()->canBeCastedFrom("InheritedFrom4"));
   }
   
   void testAncestorToChildrenCastFrom()
   {
        ASSERT_FALSE(m_cache["InheritedFrom1"]->
                     metaData()->canBeCastedFrom("DirectDescendant1"));
        ASSERT_FALSE(m_cache["InheritedFrom1"]->
                     metaData()->canBeCastedFrom("DirectDescendant2"));
        ASSERT_FALSE(m_cache["InheritedFrom1"]->
                     metaData()->canBeCastedFrom("DirectDescendant3"));
        ASSERT_FALSE(m_cache["InheritedFrom1"]->
                     metaData()->canBeCastedFrom("DirectDescendant4"));
        ASSERT_FALSE(m_cache["InheritedFrom2"]->
                     metaData()->canBeCastedFrom("DirectDescendant2"));
        ASSERT_FALSE(m_cache["InheritedFrom3"]->
                     metaData()->canBeCastedFrom("DirectDescendant3"));
        ASSERT_FALSE(m_cache["InheritedFrom4"]->
                     metaData()->canBeCastedFrom("DirectDescendant4"));
   }

   void testValidCasts()
   {
       ASSERT_EQUAL(m_cache["DirectDescendant1"]->
                    as<DirectDescendant1>()->local1(), 1);
       ASSERT_EQUAL(m_cache["DirectDescendant2"]->
                    as<DirectDescendant2>()->local2(), 2);
       ASSERT_EQUAL(m_cache["DirectDescendant3"]->
                    as<DirectDescendant3>()->local3(), 3);
       ASSERT_EQUAL(m_cache["DirectDescendant4"]->
                    as<DirectDescendant4>()->local4(), 4);
   }

   void testInheritedFrom1()
   {
       ASSERT_EQUAL(m_cache["InheritedFrom1"]->
                    as<InheritedFrom1>()->local(), 5);
       ASSERT_EQUAL(m_cache["InheritedFrom1"]->
                    as<DirectDescendant1>()->local1(), 1);
   }

   void testInheritedFrom2()
   {
       sad::Object * testbase = m_cache["InheritedFrom2"];
       InheritedFrom1 * testif1 = testbase->as<InheritedFrom1>();
       InheritedFrom2 * testif2 = sad::checked_cast<InheritedFrom2>(testif1);
       ASSERT_EQUAL(testif2->local(), 6);
       ASSERT_EQUAL(testbase->as<DirectDescendant1>()->local1(), 1);
       DirectDescendant2 * testdd2 = 
           sad::checked_cast<DirectDescendant2>(testif2);								     
       ASSERT_EQUAL(testdd2->local2(), 2);
   }

   void testInheritedFrom3()
   {
       sad::Object * testbase = m_cache["InheritedFrom3"];
       InheritedFrom1 * testif1 = testbase->as<InheritedFrom1>();
       InheritedFrom3 * testif2 = sad::checked_cast<InheritedFrom3>(testif1);
       ASSERT_EQUAL(testif2->local(), 7);
       ASSERT_EQUAL(testbase->as<DirectDescendant1>()->local1(), 1);
       DirectDescendant2 * testdd2 = 
           sad::checked_cast<DirectDescendant2>(testif2);								     
       ASSERT_EQUAL(testdd2->local2(), 2);
       DirectDescendant3 * testdd3 = 
           sad::checked_cast<DirectDescendant3>(testif2);								     
       ASSERT_EQUAL(testdd3->local3(), 3);
   }

   void testInheritedFrom4()
   {
       sad::Object * testbase = m_cache["InheritedFrom4"];
       InheritedFrom1 * testif1 = testbase->as<InheritedFrom1>();
       InheritedFrom4 * testif2 = sad::checked_cast<InheritedFrom4>(testif1);
       ASSERT_EQUAL(testif2->local(), 8);
       ASSERT_EQUAL(testbase->as<DirectDescendant1>()->local1(), 1);
       DirectDescendant2 * testdd2 = 
           sad::checked_cast<DirectDescendant2>(testif2);								     
       ASSERT_EQUAL(testdd2->local2(), 2);
       DirectDescendant3 * testdd3 = 
           sad::checked_cast<DirectDescendant3>(testif2);								     
       ASSERT_EQUAL(testdd3->local3(), 3);
       DirectDescendant4 * testdd4 = 
           sad::checked_cast<DirectDescendant4>(testif2);								     
       ASSERT_EQUAL(testdd4->local4(), 4);
   }

   void testFailCast() 
   {
        sad::Object * testbase = m_cache["DirectDescendant1"];
        try
        {
            testbase->as<InheritedFrom1>();
            // Expect exception
            ASSERT_TRUE( false ); 
        }
        catch(sad::InvalidCastException ex)
        {
            ASSERT_EQUAL(ex.fromName(), "DirectDescendant1");
            ASSERT_EQUAL(ex.toName() , "InheritedFrom1");
        }
   }

   void testCastMethod()
   {
       sad::Object * result = &_carried_object2;
       sad::Object * casted = result->metaData()->castTo(result, "CarriedObject");
       CarriedObject * test = static_cast<CarriedObject*>(casted);
       ASSERT_TRUE(&(_carried_object2.local) == test);
   }

   void testName()
   {
        DirectDescendant1 a;
        ASSERT_TRUE( a.className() == "DirectDescendant1" );
   }
   
   void testSprite()
   {
       sad::Sprite2D m;
       ASSERT_TRUE(m.metaData()->canBeCastedTo("sad::Object"));   
   }

} test_object;

