
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */

// worker.c

inherit NPC;
#include <ansi.h>

string *msg = ({
// "���ֶ��help����help news,help qj��help renwu��\n",
        "YWX�����˴���������ҳ��ַ�� http://rzrdtxy��5d6d��com/(��Ѿ�Ż���С����),��ӭ���ʣ�\n",
       "help news�����й���MUD�����±仯��\n",
       "help rzr�����й���������ϵͳ�Ľ��ܣ�\n",
//          "help rulaitask��ȡ��֮�������ϵͳ��\n",
//          "help zongshi������ܴ������θ���������ʦ��\n",
//  "help newpfm�����в��ִ�����ɫperform�Ľ��ܣ�\n",
//"����������ҳ�ṩ���߲�ѯ���ܣ����ް���վ������ӭ���ʣ�\n",
//"����topָ������ѯĿǰ������ҵ����У��Լ���toptenָ�����鿴������\n",
//"��������������һ����ϵͳ---��������help liandan�鿴��ϸ��Ϣ��\n",
//      "������̳���������� ��վ������ �� ��http://bbs.94boy.com\n",
// "�뵽��ջ¥�� �� ask bai about gift������ȡ�������\n",
"��Ҽǵ���ʱ�������ѵĵ���������ָ���ǣ�backup\n",
        });

void create()
{
        set_name("��������", ({"DTXY"}));
        set("gender", "����" );
        set("age", 13);
        set("title", "�����������ŷ���ʹ");
        set("long", "һ���ɰ���Сͯ��ÿ�츺��������ӭ��Զ�������Ŀ��ˣ�\n");
        set("combat_exp", 200);
        set("attitude", "friendly");
        set_skill("dodge", 10);
        set("per", 30);
        set("max_kee", 1500000);
        set("kee",1500000);
        set("sen",1500000);
        set("max_sen", 1500000);
        setup();
        remove_call_out("msg");
        call_out("msg",60);
}

void msg()
{
        command_function("es "+NOR+HBRED+msg[random(sizeof(msg))]+NOR);

        remove_call_out("msg");
        call_out("msg",300);

}

