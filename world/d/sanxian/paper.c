#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"�����˵�ֽ"NOR, ({ "yellow paper", "paper", "ֽ"}) );
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ���Ѿ������˵�ֽ��������ּ���ȱ��ȫ������Լ�ɱ�
        ʼ����                   
                      ����    �� 
�����֡�
\n");
                
        }
}

void init()
{
   add_action("do_remember", "remember");
}

int do_remember(string arg)
{
   object me;

   me = this_player();

   if (!arg || (arg != "yellow paper" && arg != "�����˵�ֽ"))
      return 0;
   else {
      tell_object(me, "�����������ʼ���꣬���أ����⼸���֣������εؼ��������\n");
      me->set_temp("mark/ʼ����",1);
      return 1;
   }
   return 0; 
}

