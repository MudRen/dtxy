// created by error

inherit ITEM;
inherit RANK_D;
#include <ansi.h>

void create()
{
  set_name("ˮ����", ({ "shuijing qiu", "ball" }) );
  set_weight(250);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("long", @LONG
һ����Ө͸����ˮ����������detect 1-10��̽��δ֪����.
LONG);
    set("unit", "��");
      set("value",1000);
  }
	set("special_effects", "none");  // emotion
  setup();
}

int init ()  
{   
  add_action("do_detect","detect");
  return 1;
}

int do_detect(string arg)
{
  object me,ob,other;
  int j;
  string msg_id;
  string rumor_msg,rumor_id;
  me=this_player();
  if (!arg) return notify_fail("��ֻ�ܲ�1-10��\n");
  if (sscanf(arg,"%d",j)!=1) return notify_fail("��ֻ�ܲ�1-10��\n");	
  if (j<1 || j>10) return notify_fail("��ֻ�ܲ�1-10��\n");
  j=CHANNEL_D->query("rumor_point")-j+1;
  if (j<=0) j+=10;
  write(CHANNEL_D->query("rumor_point"));
  if (! rumor_msg=CHANNEL_D->query_rumor_msg(j)) 
    return notify_fail("�������ʲô?\n");
  message_vision("$N����ˮ���������˼������\n",this_player());
  write(HIM"����ˮ�����:�ղ�'"+rumor_msg+"'��˭˵�ģ�\n"NOR);
  rumor_id=CHANNEL_D->query_rumor_id(j);
  if (rumor_id=="none")
   {
     write(HIM"ˮ����ش���:'�������й¶'\n"NOR);
     return 1;
   }
  write(HIM"ˮ���򻺻�ת��������������һ����Ӱ��\n");
  write(HIM"����ϸһ����ԭ����"HIR+rumor_id+"!\n"NOR);
  return 1;
}
