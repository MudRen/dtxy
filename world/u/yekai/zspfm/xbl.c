#include <ansi.h>
#include <zhuanshi.h>
inherit NPC;

string ask_for_zspfm();
void create()
{
        set_name(HIW"������"NOR,({"bailong ma","bailong"}));
        set("gender","����");
        set("age",40);
        set("per", 40);
        set("int", 30);
        set("kar", 30);
        set("str", 20);
        set("cor", 25);
        set("cps", 99);
        set("long", @LONG
������Ӣ��������С�����ˡ�
����������ɮ����ȡ��������ǧ����࣬�����޳�������������������й�"ת����ѧ"����Ϣ��
LONG);
        set("daoxing",1000000);
        set("combat_exp", 12345);
        set("max_force", 5000);
        set("class","bonze");
        set("eff_kee", 5000);
        set("eff_gin", 5000);
        set("eff_sen", 5000);
        set("kee", 5000);
        set("gin", 5000);
        set("sen", 5000);
        set("force", 5000);
        set("mana", 5000);
        set_skill("buddhism", 300);
        set_skill("spells", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("force", 40);
        set_skill("unarmed", 40);
        
        set("title", HIY "�˲�����" NOR);
        set("attitude", "friendly");
		/*
       set("chat_chance", 10);
        set("chat_msg", ({
                (: random_move :)
        }));
		*/
		set("inquiry", ([
                "ת����ѧ" : (: ask_for_zspfm :),
                ]) );
        setup();
}

string ask_for_zspfm() {
	object me=this_player();
	if (me->query("zspfm/number")>=2)
		return HIY"���Ѿ��������㹻��ľ�ѧ��!\n"NOR;
	if (me->query("zspfm/zspfm_xbl"))
		return HIY"�ҵľ�ѧ���Ѿ������ˣ�\n"NOR;
	if (me->query("lunhui_zhuanshi") < 1)
		return HIY"һת���ϲ��������ҵľ�ѧ!\n"NOR;
	if (me->query("zspfm/zspfm_xbl_number")*20000000 > (me->query("combat_exp")+me->query("daoxing")))
		return HIY"�����Ϊ�����������򲻵���ѧ!\n"NOR;
	me->add("zspfm/zspfm_xbl_number",1);
	if (random(me->query("int")) > 45) {
		me->set("zspfm/zspfm_xbl",1);
		me->add("zspfm/number",1);
		message( "chat", HIY"\n��ת����ѧ������ϲ"+me->query("name")+"�ڵ�"+chinese_number(me->query("zspfm/zspfm_xbl_number"))+"�ε�ʱ��������С�����ľ�ѧ��\n"NOR, users() );
		return HIY"��ϲ��ϲ����ɹ��������ҵľ�ѧ!\n"NOR;
	} else {
		return HIY"�ǳ��ź������Ե������û�������ҵľ�ѧ!\n"NOR;
	}
}
