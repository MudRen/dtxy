// ����
// by lestat 2001

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����ö��ߺ�����������Խ��Խ��ɽ��Ҳ�𽥱����б������������
����ô���ͱ����ˣ����ڵ���ȵ��ˡ�ֻ�����������һ�����ٲ���������
�գ��������£�������һ���峺�쳣�Ĵ��֮�С���Ϊ׳�ۡ�
LONG );
        set("exits", ([
		"south" : __DIR__"yanfeng",
		"west" : __DIR__"hubian",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
