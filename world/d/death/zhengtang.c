// wri by bear

inherit ROOM;
#include <ansi.h>
void jiang_jing(object where);
void finish_jing(object where);
void check_time(object where);
int do_hear();
void create ()
{
  set ("short", "���ޱ���");
  set ("long", @LONG

��������������£����������ľ����������޵ظ��������󶼻�
�������ܵ�Ӧ�еĴ��á���ǰһ�Ŵ����������������������Ա�
���Ŵ��й١�
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"new-walk5",
  "north": __DIR__"walk1",
]));
  set("hell", 1);
  set("out_doors", 1);
  set("objects", ([ /* sizeof() == 2 */
  __DIR__"npc/yanluowang" : 1,
//  __DIR__"npc/panguan" : 1,
]));
  setup();
  call_other("/obj/board/shengsi_b", "???");
}  
void init()
{
  // object where=this_object();

  //  remove_call_out("check_time");
  // check_time(where);
  // add_action("do_hear","hear");
}
void check_time(object where)
{

   mixed *local = localtime((time()-900000000)*60);
   int t = local[2] * 60 + local[1];
   int phase=((int)(t/120));
   if(phase==0&&(!query("jiangjing"))) jiang_jing(where);
if(phase==7&&query("jiangjing")) finish_jing(where);
   call_out("check_time",60,where);
}

void jiang_jing(object where)
{
message("channel:es",CYN+"��"RED"���޵ظ�"CYN"��"WHT"������[Yanluo wang]"CYN"������С���ٵ����ޱ���������\n"+NOR,users());
tell_object(where,"����������;С���Ͽ�ʼ������\n");
tell_object(where,"һʱ����ɭɭ,��������ɷɷ���ò����ˡ�\n");
    set("jiangjing",1);
}
void finish_jing(object where)
{
  tell_object(where,"������������:�����������ˡ�\n");
   set("jiangjing",0);
   }
int do_hear()
{
 object yao;
   object me=this_player();

   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
  if(!query("jiangjing"))
     return notify_fail("���޵ظ���û�п�ʼ�����ء�\n");

 if((string)me->query("family/family_name")!="���޵ظ�")
      return notify_fail("�����޵ظ�С�����ڴ�������\n");
   if(me->query("faith")>40000)
      return notify_fail("���Ѿ���һ������,���������ˡ�\n");
       tell_object(me,"�����������ƺ���������\n");
  me->start_busy(5);
   me->improve_skill("tonsillit",random((int)(me->query("spi")+me->query("int"))/2));
   me->improve_skill("gouhunshu",random((int)(me->query("spi")+me->query("int"))/2));
//  me->add("faith",1);
//  me->add("combat_exp",30);
//  me->add("potential",10);
   me->receive_damage("kee",20);
   me->receive_damage("sen",20);
  return 1;
}





