//Create By Canoe 2000.11.17
//("combat_exp")>100000||("age")>20)
// literate >80
// + dx,+ pot,+ literate
// ���϶���ĵط�
inherit ROOM;
#include <ansi.h>

string *strs = ({
        " ��������̹��ȣ�̫�������������� \n",
        " ���������������ܳ��޻��г��͡� \n",
        " ����ȡ������ʳ�����˻�������ǰ�� \n",
        " ��ũ�������ٲݣ���ԯ���ֻ������� \n",
        " ���������︷��������ˮ�鲨��,  \n",
        " ��ƽ������İ٣������޵�Ǭ���ߡ� \n",
        " ���ҿ�������ͼ����é����������.  \n",
     });
void init();
void check_time(object where);
void dushu(object where);
void finish_dushu(object where);
     
void create()
{
set ("short", "�� �� �� Ժ ");
  set ("long", @LONG

����ط����Ǵ��Ƶ���Ժ�ˣ��ܶ����ֵĶ���д�ֶ�������   
ǿ��(dushu)��,ԶԶ����������,���飺

                ������������������������
                ��                  ��
                ��    �� �� �� Ժ    ��
                ��                  ��
                ������������������������

LONG);

  set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"guozijian",
]));
  set("objects", ([ /* sizeof() == 3 */
//                  __DIR__"npc/zhangsunwuji" : 1,
                __DIR__"npc/xiucai4" : 1,

]));
  set("light_up", 1);

set("start_dushu",1);
  setup();
}

void init()
{
   remove_call_out("check_time");
   check_time(this_object());
   add_action("do_dushu", "dushu");
}

void check_time(object where)
{
   mixed *local = localtime((time()-900000000)*60);
   int t = local[2] * 60 + local[1];
   int phase=((int)(t/120));
   
   if(phase==3&&(!query("start_dushu"))) dushu(where);
   if(phase==6&&query("start_dushu")) finish_dushu(where);
   call_out("check_time",60,where);
}

void dushu(object where)
{
message("channel:chat",HIY"��̫ƽʢ������֪�£�He zhizhang�������ƹ��Ӽ࿪ʼ�ڿ�!�������!\n"+NOR,users());
     where->set("start_dushu",1);
} 

int do_dushu()
{ 
     object who=this_player();
     
if (who->query("kee")<20||who->query("gin")<20) return notify_fail("������ô�ù�?������ȥ��Ϣ��Ϣ��!\n");
if (!who->query("family/family_name")) return notify_fail("��֪�¶���ҡҡ��˵:��ʱ����û�а�ʦ�ĵ���.\n");
     if(who->is_busy())
        return notify_fail("����æ���ء�\n");
     if(!this_object()->query("start_dushu"))
        return notify_fail("���ϲſ���,�����������ʱ���ء�\n");
  //   if((int)who->query("combat_exp")<10000) return notify_fail("�����ѧ����������Ӽ������.\n");   
     if((int)who->query_skill("literate",1)>80) return notify_fail("��Ķ���д���Ѿ���һ��������.\n"); 
     if((int)who->query("combat_exp")>100000||(int)who->query("age")>20||(int)who->query("daoxing")>100000)
        return notify_fail("�㶼�Ѿ�������,������������˰�?\n");
     tell_object( who,"���ü��Ŀ������΢�̣�"+strs[random( sizeof(strs) )] );
     who->start_busy(random(6));
     who->improve_skill(   "literate",random(  (int)( who->query("spi")+who->query("int") )  )   );
     who->add("daoxing",12);
     who->add("potential",5);
      who->receive_damage("kee",20);
       who->receive_damage("sen",20);
     tell_object(who,"������Լ������˽���Щ����ķ�չ���̣�\n");
     return 1;
}

void finish_dushu(object where)
{
     tell_object(where,"��֪�¿�������,˵��:Ӧ���¿���,��ɢ�ɡ�\n");
     where->delete("start_dushu");
}

