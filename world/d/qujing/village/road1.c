//Cracked by Roath
//  ����֮�� ������
//  by happ@YSZZ 2000.4.7
//  /d/qujing/village/road1.c

inherit ROOM;

void create ()
{
  set ("short", "���С·");
  set ("long", @LONG

һ·�Ϸ紵��Ҷ��·��ӡ��һЩ����Ľ�ӡ���������е��ر��
���ɣ���ȡ����������һ·Ͷ������������ɽ��ˮ����������Ұ��
�вݣ��㲻��̾Ϣ�����Ѹ�ٰ���

LONG);
  set("exits", ([
        "west"  : __DIR__"road2",
        "eastdown" : "/d/qujing/liusha/riverside",
          ]));
  set("outdoors","cz");
  setup();
}

void init()
{
        object me;
    me=this_player();
     if (((me->query("fangcun/panlong_wzg_rsg")=="done")||(me->query("fangcun/panlong_wzg")=="done"))&&(me->query_temp("set_village")!="done"))
	{    
	  me->add_temp("wzg_rulaifo",1);
	  me->set_temp("set_village","done");
	}
	     
}
