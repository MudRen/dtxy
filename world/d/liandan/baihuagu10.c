//By Canoe
inherit ROOM;
#include <room.h>
#include <ansi.h>
void create ()
{
 set ("short", "��ũҩ��");
  set ("long", @LONG

�һ�����������,Ǳ�ݲ���û����.����������,��ҩ
Ʒ�ֺܶ�,˵�����Ͳ���ʲô�������.

LONG);

  set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"baihuagu12",
  "south" : __DIR__"road3",
  "east" : __DIR__"baihuagu32",
  "west" : __DIR__"baihuagu22",
]));
  if(!random(6)) set("outdoors",1);
  setup();
}

void init() {
  object me=this_player();
  if (present("baicao shen",this_object())) return;
  if (!present("yao chu",me)) return;
   me->start_busy(random(2)+1);
  tell_object(me,GRN"���ܲ�ľ����,��ٲ�ά�衣\n"NOR);
 
  if (random(10)) return;
  else {
  remove_call_out("greeting");
  call_out("greeting",1,me,this_object());
      }
}

void greeting(object me,object env) {
  if (!me || environment(me)!=env) return;
   me->start_busy(2);
  tell_object(me,MAG"�㿴���ݴ����ƺ���Щ����������ͣס�Ų����뿴����ϸ��\n"NOR);
  call_out("greeting1",2,me,env);
}


void greeting1(object me,object env) {
  if (!me || environment(me)!=env) return;
  
  if (random(4)) 
     {
      environment(me)->set_temp("wayao1",1);
      environment(me)->delete_temp("wayao2");
      tell_object(me,MAG"�����ǰһ��������һ��"HIY"��ͨҩ��"NOR MAG"���ڲݴ��С�\n\n"NOR);
     }
  else {
      environment(me)->set_temp("wayao2",1);
      environment(me)->delete_temp("wayao1");
      tell_object(me,MAG"�����ǰһ��������һ��"HIR"���ҩ��"NOR MAG"���ڲݴ��С�\n\n"NOR);
     }      
}

