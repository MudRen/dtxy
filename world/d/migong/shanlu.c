//ɽ��:shanlu.c 
//tomcat
inherit ROOM;

void create()
{
	set("short", "ɽ��");
	set("long", @LONG
����һ����ֱ��ɽ·��ǰ�����죬һֱ��û������֮�У�
��֪��ô���������Խ��Խϡ�٣��㲻�������ֹ������ʲ
ô�°ɣ����������������ǰ���š�

LONG
	);

	set("outdoors", "migong");

	set("exits", ([ /* sizeof() == 3 */
	"west" : __DIR__"zhanchang/entry",
	"east" : "/d/changan/zhongnan",
 ]));

	setup();
	replace_program(ROOM);
}

