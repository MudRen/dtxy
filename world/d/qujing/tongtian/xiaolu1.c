// create by snowcat.c 12/15/1997

inherit ROOM;

void create ()
{
  set ("short", "С·");
  set ("long", @LONG

С·�������䣬·��������ʯ���ѱ������ĳ���ѹ��������ӡ��
·����һ�ÿ����������Ÿ�������������������·��������
ũ������ׯ�ڡ�

LONG);

  set("exits", ([
        "southeast"   : __DIR__"hexi2",
        "west"   : "/d/qujing/jindou/shanlu5",
      ]));
  set("outdoors", __DIR__);

  setup();
}

void init()
{
        object me;
    me=this_player();
     if (((me->query("fangcun/panlong_wzg_rsg")=="done")||(me->query("fangcun/panlong_wzg")=="done"))&&(me->query_temp("set_tongtian")!="done"))
	{
		 me->add_temp("wzg_rulaifo",1);
		 me->set_temp("set_tongtian","done");
	}
}


