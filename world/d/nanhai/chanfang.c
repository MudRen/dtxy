//Cracked by bear
// Room: /d/nanhai/chanfang
inherit ROOM;

#include <ansi.h>
void jiang_jing(object where);
void finish_jing(object where);
void check_time(object where);
int do_hear();
void create ()
{
  set ("short", "����");
  set ("long", @LONG

��������ɽ���˵��������������ĵط���ֻ������ɮ������
һ��ߺ������ȭŪ�ţ����⼸������ϰ�������ݽǰ��ż���
������ǹ��
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"zoulang",
]));
 set("no_clean_up", 1);
set("light_up", 1);
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/zhangchan" : 1,
]));

  setup();
}
void init()
{
   //object where=this_object();

    //remove_call_out("check_time");
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
message("channel:es",CYN+"��"RED"�Ϻ�����ɽ"CYN"��"CYN"����ɮ[Zhangchan seng]"CYN"�����ڿ�ʼ�����ҷ�����֮�ޱ߷𷨡�\n"+NOR,users());
tell_object(where,"���Ъ�ս���̳���������������Ρ�\n");
tell_object(where,"�ε�ˮ��ɽ��������Ȼ͸����ʦ�ء�\n");
tell_object(where,"�ŵ��ƣ�����Ҫ͸��ʦ�أ�����Ҫ����·������ز�͸����·�������������ݸ�ľ���顣\n");
tell_object(where,"�ҵ��������ʦ�أ�ֻ��һ�����ޡ��֣�����һ�أ�����Ŀ֮Ϊ�����Źء���\n");

   tell_object(where,"���͸����һ�أ������ܹ��׼����ݣ������ܹ���������ʦ���ֹ��У�üë˺�ᣬͬһ�ۼ���ͬһ���ţ�����죡\n");
   set("jiangjing",1);
}
void finish_jing(object where)
{
   tell_object(where,"����ɮ˵�����ҽ��ģ�Ҳ����������ʦ�������֪ʶ�����ģ������Ǵ����������������ģ����Զ���ʰ�����۶��ѡ�\n");
   set("jiangjing",0);
     set ("long", @LONG
    ��������������
LONG);
}
int do_hear()
{
 object yao;
   object me=this_player();

   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
   if(!query("jiangjing"))
      return notify_fail("����ɮ��û��ʼ���ڷ��ء�\n");

 if((string)me->query("family/family_name")!="�Ϻ�����ɽ")
      return notify_fail("���ɵ��Ӳ�����������\n");
   if(me->query("faith")>40000)
      return notify_fail("��Է𷨵�����Ѿ��Գ�һ���ˡ�\n");

    tell_object(me,"�����Ա����ţ����š����ĸ����ȹ��ˡ�\n");
   me->start_busy(5);
   me->improve_skill("lotusforce",random((int)(me->query("spi")+me->query("int"))/2));
 //  me->improve_skill("buddhism",random((int)(me->query("spi")+me->query("int"))/2));
//  me->add("faith",1);
//  me->add("combat_exp",30);
//  me->add("potential",10);
   me->receive_damage("kee",20);
   me->receive_damage("sen",20);
   return 1;
}

