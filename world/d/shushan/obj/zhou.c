#include <ansi.h>
inherit ITEM;

void create()
{
  set_name(HIC"�ɷ������"NOR, ({ "fu" }) );
  set_weight(350);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("long", "һ����ɽ���������\n");
    set("unit", "��");
  }
  set("value",0);
  set("no_drop",1);
  set("no_get",1);
//  set("no_give",1);
  set("no_put",1);
  setup();
}

int init ()  
{   
  add_action ("do_back", "back");
}

int do_back()
{
    object me,ob;
    me=this_player();
    ob=this_object();
	message_vision(HIY"\n\nһ�������ס��$N����Ӱ,$Nһ��ѣ��,ֱ����ȫ��Ҫ��˺����һ��������\n\n"NOR,me);
    
	me->move("/d/shushan/shanjiao");
	me->unconcious();
   destruct(ob);
return 1;
}


