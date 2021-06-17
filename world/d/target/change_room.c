// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// Room: some place in ��ţ����
// inside2.c
#include "ansi.h"

inherit ROOM;
void init();
void dance(object where);
void finish_dance(object where);
void check_time(object where);
/* void send_drug(object where); */
int do_enjoy();

void create ()
{
  set ("short", "��˼��");
  set ("long", @LONG

���������ʹ�������¯�е���һ�����㣬�������ơ����ط���һ�Ż����
��ʯ�󰸣����϶����������˷�������ʮ�������⣬��ɫ��Ͳ����һ����
�������һ����Ҥ���ң�����������ˮ����İ׾ջ����鰸�������ż���
��ֽ(paper)���ּ����㣬�����϶�ٰ�����֮����Ϳ�

LONG);
   set("item_desc", ([ /* sizeof() == 1 */
  "paper" : "ֽ�Ϸ���������д��һ�仰���첻�ϣ����Ѿ�������˫˿��������ǧǧ�ᡣ
",
]));
  set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"huilang.c",
]));
  set("objects", ([ /* sizeof() == 2 */
  __DIR__"npc/change.c" : 1,
 "/d/obj/flower/juhua.c":1,
]));
/* set("valid_startroom",1); */
  setup();
}

void init()
{
   object where=this_object();
   remove_call_out("check_time");        
   check_time(where);
   add_action("do_enjoy","enjoy");
}


void check_time(object where)
{
   mixed *local = localtime((time()-900000000)*60);
   int t = local[2] * 60 + local[1];
   int phase=((int)(t/120));
   
/*
  if(local[3]==1&&(!query("senddrug"))) send_drug(where);
    if(local[3]==2)delete("senddrug");
*/
   if(phase==3&&(!query("dance"))) dance(where);
   if(phase==4&&query("dance")) finish_dance(where);
   call_out("check_time",60,where);
}
void dance(object where)
{
message("channel:es",HIG+"���¹����϶�(Chang e)��îʱ��,�������ˡ�\n"+NOR,users());
   tell_object(where,"�϶�����ɴȹ�������������,����ǣ�\n");
   tell_object(where,"���Ϊ֮��ɫ�����Ϊ֮���ݣ�\n");
   tell_object(where,"����ֻΪ�����У��˼����м��ؼ�?\n");
   tell_object(where,"����������һ������.\n");
   set("dance",1);
     set ("long", @LONG
�������϶�ľ�����Ҳ����������ĵط���������Χϡϡ�������ż�λ����,
���϶���������۷���������(enjoy)���������.
LONG);
}

void finish_dance(object where)
{
   tell_object(where,"�϶��߳���أ����Ե������칦�ε��˽�����\n");
   set("dance",0);
     set ("long", @LONG
���������ʹ�������¯�е���һ�����㣬�������ơ����ط���һ�Ż����
��ʯ�󰸣����϶����������˷�������ʮ�������⣬��ɫ��Ͳ����һ����
�������һ����Ҥ���ң�����������ˮ����İ׾ջ����鰸�������ż���
��ֽ(paper)���ּ����㣬�����϶�ٰ�����֮����Ϳ��
LONG);
}

int do_enjoy()
{
   object me=this_player();
   
   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
   if(!query("dance"))
      return notify_fail("�϶�û�����أ���������ʲô?\n");
   if((string)me->query("family/family_name")!="�¹�")
      return notify_fail("���ɵ��Ӳ���������!\n");
     if(me->query("faith")>5000)
      return notify_fail("�����Ϊ�Ѿ��㹻�ߣ������������ˡ�\n");      
   
    tell_object(me,"�������������������򣬲���ü����Ц��\n");
me->start_busy(4+random(1));
  me->add("faith",1);
  me->improve_skill("moonshentong",random((int)(me->query("spi")+me->query("int"))/2),1);
  me->add("combat_exp",30);
  me->add("potential",10);
   me->receive_damage("kee",20);
   me->receive_damage("sen",20);   
   tell_object(me,"������¹��ɷ������ˣ�\n");
   return 1;       
}

/*
void send_drug(object where)
{
    object master=present("chang e",where);
    object daoshi,ob,cart;
    
    if(master){
        set("senddrug",1);
        tell_room(where,"��������˵�������³������������ǵ�ҩ����ҩ���ˡ�");
        tell_room(where,"��������̾��һ����������˵��������ħ���У���֪��λ����Ը����ҩ�ģ�");
    }
    
    say("һ��ҩ�ĳ�����Ժʻ����\n");
        
    ob=new(__DIR__"obj/cart");
    ob->move(where);
    cart=ob;
        
    daoshi=new(__DIR__"npc/drugdao");
    daoshi->move(where);
    daoshi->get_quest(__DIR__"npc/dartway1");
    daoshi->set_cart(cart);
    daoshi->wait_go(where);
        
    ob=new(__DIR__"obj/yaocai");
    ob->move(cart);
}
*/
