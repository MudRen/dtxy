#include <ansi.h>
inherit ITEM;
int do_eat(string);
void init();
void init ()
{
  object me = this_object();
  object who = this_player();
  object where = environment();
  if (!me->query("my_owner") &&
      interactive (who))
  me->set("my_owner",who->query("id"));
  add_action ("do_eat", "eat");
  
}
void create()
{
        set_name(HIW "�˲ι�" NOR, ({"renshen guo", "renshenguo", "guo"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("long", "�װ����ֵ�һö�˲ι�����ǧ��һ��������ǧ��һ���������ǧ��ŵ��죬ʵ����ؼ���鱦��\n");
                  set("value", 5);
set("no_put",1);
set("no_drop",1);
set("no_sell",1);
                set("drug_type", "��Ʒ");
        }
  
        set("is_monitored",1);
        setup();
}

int do_eat(string arg)
{
        int howmany;

        object me = this_player();
      
        if (!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if(!this_object()->query("my_owner"))
                return notify_fail("���õ������?\n");
if ((string)environment(me)->query("short")=="������" )
return notify_fail("������ôΣ�ջ���ʲô��������\n");
        howmany = (int)me->query("rsg_eaten");
  
        me->set("food", (int)me->max_food_capacity());

        if(me->query("id")==this_object()->query("my_owner"))
        {
        
        if( howmany <= 100 ) me->add_maximum_force(0);
        if( howmany <= 100 ) me->add_maximum_mana(0);
        }
        else  message_vision(HIY "�������Լ����Ͷ��ɹ�!\n" NOR, me);  
//       me->set("rsg_eaten", howmany+1);

        message_vision(HIW "$N���˲ι�������һ�����̲�ס���һ�����˲ι����˲ι����������˲ι��� \n˵���˷ܵö������˹�ȥ��\n" NOR, me);  

//         me->set("obstacle/wuzhuang","done");

        //for live forever...
        if( me->query("rsg_eaten") >= 36 )
        {
                me->announce_live_forever( me->query("name")+"��ֲ�и�س��˲ι��������޳��˲����ֻأ��Ӵ����������⣬���������У��������������ˣ�" );
        }

//         me->unconcious();
 if (!wizardp(me))
         me->unconcious();
        destruct(this_object());

        return 1;
}
