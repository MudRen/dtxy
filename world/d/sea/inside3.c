//modified by bear

inherit ROOM;
#include <ansi.h>
void jiang_jing(object where);
void finish_jing(object where);
void check_time(object where);
int do_hear();
void create ()
{
  set ("short", "��������");
  set ("long", @LONG

����֮����һ���飬��ŵ��һ���յ�ͨ��������������ʯ������ɣ�����
���л�Ƕ�������鱦������ǽ�Ϲ������������������൱�ĳ¾ɡ�������
�ϱ�������ƫ�

LONG);

  set("exits", ([ /* sizeof() == 2 */
  "westdown" : __DIR__"inside2.c",
  "east" : __DIR__"inside4",
]));
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/longwang" : 1,
]));
//      
        set("water", 1);
//  
  setup();
}

void init()
{
   //object where=this_object();

  //  remove_call_out("check_time");
   //check_time(where);
   //add_action("do_hear","hear");
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
message("channel:es",CYN+"��"YEL"��������"CYN"��"YEL"����[ao guang]"YEL"�����ڿ�ʼ��������������ˮ֮����\n"+NOR,users());
tell_object(where,"�ĺ����������ǲ�ڷ��䣬ר�ܽ��ꡣ\n");
tell_object(where,"�ĺ�����֮�������ڶ����������������������ˮ�塣\n");
tell_object(where,"�Ҵ����书������ˮ��ռ�˼�������ơ�\n");

   tell_object(where,"�������ı���Ա��ŵ��ӵĳɳ�Ҳ�Ǵ��кô���\n");
   set("jiangjing",1);
}
void finish_jing(object where)
{
tell_object(where,"��������˵������ȥ������ı�ˮ֮������������ˡ�\n");
   set("jiangjing",0);
     set ("long", @LONG
     ���������Ƕ�������������˵Щʲô��
LONG);
}
int do_hear()
{
 object yao;
   object me=this_player();

   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
   if(!query("jiangjing"))
return notify_fail("�������㻹û��ʼ���ڱ�ˮ֮���ء�\n");

 if((string)me->query("family/family_name")!="��������")
      return notify_fail("���ɵ��Ӳ�����������\n");
   if(me->query("faith")>40000)
      return notify_fail("����������ˮ֮�����Ѿ����Ĳ���ˡ�\n");

    tell_object(me,"�����Ա����ţ����š������Ա��ŵı�ˮ֮����������\n");
   me->start_busy(5);
   me->improve_skill("dragonforce",random((int)(me->query("spi")+me->query("int"))/2));
   me->improve_skill("seashentong",random((int)(me->query("spi")+me->query("int"))/2));
//  me->add("faith",1);
//  me->add("combat_exp",30);
//  me->add("potential",10);
   me->receive_damage("kee",20);
   me->receive_damage("sen",20);
   return 1;
}



int valid_leave()
{
    if(
       (present("dao kan dao", this_player()))
       || (present("jiu gu cha", this_player()))
       || (present("mei hua chui", this_player()))
       || (present("hua gan ji", this_player()))
      )
        return notify_fail("�����������������ߣ�\n");
    return ::valid_leave();
}

