// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// Room: /d/qujing/wudidong/inner-tang.c

inherit ROOM;

#include <ansi.h>
void jiang_jing(object where);
void finish_jing(object where);
void check_time(object where);
int do_hear();
void create ()
{
  set ("short", "���");
  set ("long", @LONG

���������С�����ر��ߣ�����׼������ϯ��һ��Ů�����и�����
���ٵʹ������ΰ����Ц������ָ������С����ȫ�����Լ��㺹��
�졣������Ⱥ��һ�죬һʱ��Ҳ���˷���������ط�Ҳ�Ǵ�������
���������ĵط�����ֻҪ��(hear)���Ϳ����ˡ�
LONG);

  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/yushu" : 1,
]));
  set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"tang-gate",
]));

  setup();
}

void init()
{
   //object where=this_object();

   // remove_call_out("check_time");
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
message("channel:es",CYN+"��"WHT"�ݿ�ɽ�޵׶�"CYN"��"WHT"����[Yu shu]"CYN"�����ڿ�ʼ���������޵׶��ı��䡣\n"+NOR,users());
tell_object(where,"��ӿ����˵������������ӵ�ζ����ʵ���Ǻð���\n");
tell_object(where,"����Ҫ�ĺ����������������ˮ��\n");
tell_object(where,"������ӳԵľ������ʣ����ܷ��ã��������Ҫ�������ɰ��ӡ�\n");

   tell_object(where,"Ҫ���ǣ��˵����฽��������Ϊ������\n");
   set("jiangjing",1);
}
void finish_jing(object where)
{
   tell_object(where,"��ӿ����˵������ȥ��������������������Ρ�\n");
   set("jiangjing",0);
     set ("long", @LONG
    ��������Щ��ģ���������֣����ǵ��۾�����
���ƺ���Ҫ���ˣ�����������ӿ����˵Щʲô��
LONG);
}
int do_hear()
{
 object yao;
   object me=this_player();

   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
   if(!query("jiangjing"))
      return notify_fail("��ӿ���˻�û��ʼ���ڱ����ء�\n");

 if((string)me->query("family/family_name")!="�ݿ�ɽ�޵׶�")
      return notify_fail("���ɵ��Ӳ�����������\n");
   if(me->query("faith")>40000)
      return notify_fail("�������������С�£����Ѿ��ǵ�ӿ���˵�ʦ���ˡ�\n");

    tell_object(me,"�����Ա����ţ����š�����������������ӵ���ζ��\n");
   me->start_busy(5);
   me->improve_skill("huntian-qigong",random((int)(me->query("spi")+me->query("int"))/2));
   me->improve_skill("yaofa",random((int)(me->query("spi")+me->query("int"))/2));
//  me->add("faith",1);
//  me->add("combat_exp",30);
//  me->add("potential",10);
   me->receive_damage("kee",20);
   me->receive_damage("sen",20);
   return 1;
}

