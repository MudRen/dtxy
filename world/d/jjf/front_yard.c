// ���������䳡
//2001 by lestat

inherit ROOM;
#include <ansi.h>
void yan_wu(object where);
void finish_yan(object where);
void check_time(object where);
int do_yanwu();

void create ()
{
  set ("short", "���䳡");
  set ("long", @LONG
�����ĳ�����������ϸϸ�Ļ����������ʺ�����(yanwu)�������м�
���ظ��ҽ��������䡣�����һλ�ܼҴ��������ڱ����ֹۿ���
����ʱ����ǰȥָ��һ�������ر��Ϲ��ż�����ɳ��(sandbags)����
֪��ʲô�ô��������м��ưܵ�С�ݣ��Ŵ��������ˣ��뽫��������
���ķ������롣
LONG);

  set("item_desc", ([ /* sizeof() == 3 */
  "window" : "�Ŵ����������ˣ�ǽ�Ϻ�����Щ���ҵĺۼ���\n",
  "door" : "
�Ŵ����������ˣ�ǽ�Ϻ�����Щ���ҵĺۼ���\n",
  "sandbags" : "
�������ص�ɳ�����������Ŵ��(da)����\n",
]));
  set("outdoors", 1);
  set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"gate",
  "south" : __DIR__"front_yard2",
  "east" : __DIR__"majuan",
  "southwest" : __DIR__"guest_bedroom",
]));

  set("objects", ([
                   __DIR__"npc/qinfu": 1,
        __DIR__"npc/xiaotong": 2,
                   ]));

  setup();
}

void init()
{   //object where=this_object();
    //remove_call_out("check_time");
   //check_time(where);
   //add_action("do_yanwu","yanwu");
  add_action("do_hammer", "hammer");
  add_action("do_da", "da");
}

void check_time(object where)
{

   mixed *local = localtime((time()-900000000)*60);
   int t = local[2] * 60 + local[1];
   int phase=((int)(t/120));
   if(phase==3&&(!query("yanwu"))) yan_wu(where);
if(phase==4&&query("yanwu")) finish_yan(where);
   call_out("check_time",60,where);
}
void yan_wu(object where)
{
message("channel:es",CYN+"��"RED"���ƽ�����"CYN"��"WHT"��ҧ��[Cheng yaojin]"CYN"�����ƽ������ڽ����䳡�����\n"+NOR,users());
tell_object(where,"�ظ�����;�ڽ�ʿ���Ͽ�ʼ���䡣\n");
tell_object(where,"ս������,һƬ��ʿ���ź������������\n");
   set("yanwu",1);
}
void finish_yan(object where)
{
   tell_object(where,"�ظ���������:�ڽ�ʿ�����ˡ�\n");
   set("yanwu",0);
//     set ("long", @LONG
//    �����ĳ�������������վ���˷���,ս������,�����չ��
//LONG);
}
int do_yanwu()
{
 object yao;
   object me=this_player();

   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
   if(!query("yanwu"))
      return notify_fail("��������û�п�ʼ���,��һ�����ݵ�ʲô�䡣\n");

 if((string)me->query("family/family_name")!="������")
      return notify_fail("�ǽ�������ʿ�������䡣\n");
   if(me->query("faith")>40000)
      return notify_fail("���Ѿ���ѫ׿Խ,���������ˡ�\n");

    tell_object(me,"����������ս�����ڽ�ʿһ�����䡣\n");
   me->start_busy(5);
   me->improve_skill("lengquan-force",random((int)(me->query("spi")+me->query("int"))/2));
   me->improve_skill("baguazhou",random((int)(me->query("spi")+me->query("int"))/2));
//  me->add("faith",1);
//  me->add("combat_exp",30);
//  me->add("potential",10);
   me->receive_damage("kee",20);
   me->receive_damage("sen",20);
   return 1;
}

int do_da(string arg)
{
  object me=this_player();
  int unarmedskll=(int)(me->query_skill("unarmed", 1)/2);
  int maxlevel, exp=(int)me->query("combat_exp");
 
  if( !arg || !((arg == "sandbags") || (arg == "ɳ��")))
    return notify_fail("��Ҫ��ʲô��\n");
  if( me->query("kee") < (int)(me->query("max_kee")/5))
    return notify_fail("�ٴ���ȥ��������ģ�\n");
  if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
    return notify_fail("�ñ������ɳ���򻵵ģ�\n");
  if (!((string)me->query("family/family_name")=="������"))
    {
      message_vision("$Nһȭ��ɳ����ȥ������ɳ��һ��������\n", me);
    }
  else
    {
      message_vision("$N�þ�������ɳ����ȥ�����ɳ��ֱ�Ρ�\n", me);
      if (exp*10 <= (unarmedskll*unarmedskll*unarmedskll))
   {
     me->receive_damage("kee", (int)me->query("max_kee")/10);
     return notify_fail("��ĵ��в����ߣ����ܴӴ�ɳ����ѧ����֪��\n");
   }
      if (unarmedskll*2<240)
   {
     me->improve_skill("unarmed", (me->query("str") + me->query("con"))*10);
     tell_object(me, "�������һЩ����ȭ�ŷ�������š�\n");
   }
      else
   {
     tell_object(me, "����ɳ���Ϸ��˰��쾢������ʲôҲû��ѧ����\n");
   }
    }
  me->receive_damage("kee", (int)me->query("max_kee")/10);
  return 1;
}

int do_hammer(string arg)
{       
  object me;
  me=this_player();
  if ( !present("hammer", me) || (arg != "door"))
    return notify_fail("�����ȭͷ��ǽ����ȥ����������������ͦ�ۣ�\n");
  else
    message_vision("$N����󴸣���ǽ����ȥ��\n", me);
  if((int)me->query_temp("mark/����") < 1)
    {
    me->set_temp("mark/����", 1);
  }
  me->add_temp("mark/����", 1);
  me->receive_damage("kee", 40);
  if((int)me->query_temp("mark/����") > 5)
    {
    message_vision("$N��ǽ�ҿ���һ��������æ���˽�ȥ��\n", me);
    me->set_temp("mark/����", 1);
    me->set_temp("mark/��������", 1);
    me->move("/d/jjf/mishi");
    return 1;
  }
  return 1;
}
