// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// Room: /d/33tian/west1
#include <ansi.h>
inherit ROOM;
void jiang_jing(object where);
void finish_jing(object where);
void check_time(object where);
int do_hear();

void create ()
{
  set ("short", "���ʹ�");
  set ("long", @LONG
���������춵�ʹ���.�˹�λ����ʮ����֮��,һ����̫��
�Ͼ���ס��.������һ����ҩ¯,��������ͯ������ҩ¯��ɿ��,
������������һ�ɷҷ��ĵ�ҩ��Ϣ,̫���Ͼ������ڴ�����
�����澭,����(hear)�����ǳ.
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"doushuai-gate",
]));
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/laojun": 1,
]));
  setup();
}
void init()
{
   // object where=this_object();
   // remove_call_out("check_time");
   // check_time(where);
   // add_action("do_hear","hear");
}
void check_time(object where)
{
   mixed *local = localtime((time()-900000000)*60);
   int t = local[2] * 60 + local[1];

   int phase=((int)(t/120));
   if(phase==3&&(!query("jiangjing"))) jiang_jing(where);
   if(phase==4&&query("jiangjing")) finish_jing(where);
   call_out("check_time",60,where);
}
void jiang_jing(object where)
{
message("channel:es",CYN+"��"MAG"�˾���������"CYN"��"HIW"̫���Ͼ�[Taishang laojun]"+NOR+HIY"�������ڶ��ʹ��������¾���\n"+NOR,users());
tell_object(where,"������̫���Ͼ���������֪���ۣ�����ƣ�Ϊ����Ϫ��Ϊ����Ϫ�����²��룬������Ӥ����\n");
tell_object(where,"������̫���Ͼ���������֪��ף������裬Ϊ���¹ȡ�Ϊ���¹ȣ��������㣬�������ӡ�\n");
tell_object(where,"������̫���Ͼ���������֪��ף�����ڣ�Ϊ����ʽ��Ϊ����ʽ�����²�߯���������޼���\n");
tell_object(where,"������̫���Ͼ�����������ɢ��Ϊ����ʥ����֮����Ϊ�ٳ����ʴ��ǲ��\n");
tell_object(where,"........................................\n");
   set("jiangjing",1);
}
void finish_jing(object where)
{
   tell_object(where,"̫���Ͼ�˵���������Ϣ�ɡ�\n");
   set("jiangjing",0);
}
int do_hear()
{
 object yao;
   object me=this_player();

   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
   if(!query("jiangjing"))
      return notify_fail("̫���Ͼ���û�п�ʼ���ڵ��¾���\n");

 if((string)me->query("family/family_name")!="��ׯ��")
      return notify_fail("���ɵ��Ӳ�����������\n");
   if(me->query("faith")>40000)
      return notify_fail("̫���Ͼ�����˵���������ȥ��Щ�������������ˡ�\n");
   tell_object(me,"�㲻����̫���Ͼ��Ľ������������ˡ�\n");
   me->start_busy(5);
   me->improve_skill("taiyi",random((int)(me->query("spi")+me->query("int"))/2));
   me->improve_skill("zhenyuan-force",random((int)(me->query("spi")+me->query("int"))/2));
//   me->add("faith",1);
//   me->add("combat_exp",30);
//   me->add("potential",5);
   me->receive_damage("kee",20);
   me->receive_damage("sen",20);
   return 1;
}
