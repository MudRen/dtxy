//zhangsun wuji

inherit NPC;
#include <ansi.h>
#include <quest.h>

void create()
{
	set_name("���ϰ�", ({"boss dachang", "boss"}));
	set("title", "�����޼�");
	set("age", 40);
	set("per", 15);
	set("long","
���ϰ�ԭ����󳦣������ǳ�����������å�����ң�������
֮һ���дα�����ʹ����Դ����𣬰�������֮�ʶ�ʷ���ơ���
�������ܴ����˵Ĺ���ʱ���Ȼ���򡣴Ӵ˷ܷ����飬Ǳ��ϰ�䣬
�Ĳ����䲻�ͺ���Ȼ�º����̣����ڳɾ��˽���ľ��档����
������󳣣������ۣ�ٲȻ�¹����ˡ�\n");
	

	set("quest_type", "knight");
        set("inquiry", ([
		"�ܺ�" : (: give_quest :),
		"mihan": (: give_quest :),
	]));	

	setup();
	carry_object("/d/obj/cloth/choupao")->wear();
}