//Cracked by Roath
inherit ROOM;

void create ()
{
	set ("short", "���㷻");
	set ("long", @LONG

���㷻��������ɽ��ׯ��֮�⣬һ�����͵������㣬��ͷ��Ը
���Ҫ��ת�ˡ���ǰ��һ�����㰸���������򵭵���ȼ��������
��ի�����׿ͷ����������Ϣ��ի��
LONG);

	set("exits", 
	([ //sizeof() == 4
		"southdown" : __DIR__"gate",
		"northup" : __DIR__"secondgate",
	]));
	
	set("objects", 
	([ //sizeof() == 1
		//__DIR__"npc/***" : 1,
	]));


	set("outdoors", "wuzhuang");

	setup();
}
int valid_leave(object me,string dir)
{
    if ( !me->query_temp("weapon") && !me->query_temp("newbie")&&me->query_temp("ob")&&present("pink cloth",me))
   { 
        CONVERT_D->done((string)me->query_temp("ob"),me);
          me->set_temp("newbie",1);
   }
   return ::valid_leave(me, dir);
}