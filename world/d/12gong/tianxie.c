// by HAPP@YSZZ

inherit ROOM;
int block_cmd(string);
void create ()
{
        set ("short", "�ڰ˹���Ы��");
        set ("long",@LONG
�ڹ�ϣ��ʱ�����������ٵĶ��Ӱ�������λ�����Ķ�ʿ�������������꣬������ǿ
�����ǵ����ӣ������൱��Ů��Ե��������Ҳ�൱�Ժ����������Բ��ѵĹ������£�����
��û�б��Ҹ������ˣ�����Ů���������൱���ã����ɳ�һֻ�Ͷ�����Ыȥץ����������
����ԭ���ĵط�����Ы�����ﵽ����֪��İ�������ߣ����䶾�������Ÿ���ȥ����
��������������������Ӧ������������������Ϊ�д˹�ѫ���������Ͼ�����Ы������ʹ��
�ڣ�ֻҪ��Ы���Ӷ������𣬰�������(�Ի���)�͸ҽ���������ƽ�����س�û.

LONG);
        set("exits", ([
        "eastup"    :       __DIR__"tx2rm1",
        "southdown"  :       __DIR__"tc2tx2",        
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/tianxie" : 1,
        ]));
        set("outdoors", "12gong");
        setup();
}

int valid_leave(object me, string dir)
{
        if ( present("tian xie") && dir == "eastup" )
        return notify_fail("������Ц��:�ȹ��������˵��\n");
        return ::valid_leave(me, dir);
}

void init()
{
    add_action("block_cmd", "", 1);
}
int block_cmd(string args)
{
string verb;
verb = query_verb();
    if (verb == "recall") return 1;
    return 0;
}
