// snowcat moved to /d/qujing/wuji

inherit ROOM;

void create ()
{
  set ("short", "ɽ��");
  set ("long", @LONG

ɽ����᫲�ƽ������ɽ�������������ƣ�����ʮ���ն�Ⱥ�ͻ��ƣ��ѱ�
�����ϱ�����紵�����е����˺�����
LONG);

  set("outdoors", __DIR__"");
  set("exits", ([ /* sizeof() == 2 */
  "northwest" : "/d/qujing/chechi/shatan3",
  "northeast" : __DIR__"shandao4",
  "north" : "/d/qujing/kusong/songlin1",
]));

  setup();
}

void init()
{
        object me;
    me=this_player();
     if (((me->query("fangcun/panlong_wzg_rsg")=="done")||(me->query("fangcun/panlong_wzg")=="done"))&&(me->query_temp("set_wuji")!="done"))
	{
		 me->add_temp("wzg_rulaifo",1);
		 me->set_temp("set_wuji","done");
	}
}
