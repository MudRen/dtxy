//captor.c

inherit NPC;
#include <ansi.h>
#include <auto_move.h>
int msg();

void create()
{
	mapping name;
	
	name=NAME_D->random_name("japan");
	set_name(name["name"], name["id"]);
	set("title", name["title"]);
	set("long", "��˵���ձ�����������ʿ��\n");
	set("age", 20+random(30));
	set("per", 15+random(10));
	set("gender", "����");
	
        set("combat_exp", 100000+random(100000));
        set("wuxue_exp", 500000+random(500000));
        set_skill("unarmed", 100+random(100));
        set_skill("dodge", 100+random(100));
//        set_skill("renshu", 100+random(100));
        set_skill("parry", 100+random(100));
        set_skill("blade", 100+random(100));
        map_skill("dodge", "renshu");
        set("max_kee", 1000+random(1000));
        set("max_sen", 1000+random(1000));
        set("max_force", 1000+random(1000));
        set("force", 3000);
        set("force_factor", 70);
        set("mana_factor", 20);
        set("max_mana", 500+random(500));
        set("mana", 2000);

	set("chat_chance", 20);
	set("chat_msg", ({
		(: random_move :),
		(: msg :),
	}));

	set("move_msg/out", "$N��ͷ����һ�䡰�Ԥդ�Ĥ�!�����Ͳ����ˡ�\n");
	set("move_msg/int", "$N��Ȼ�ӵ��ϴ��˳�����\n");
	set("move_msg/dis", "$N��ͷ����һ�䡰�Ԥդ�Ĥ�!�����Ͳ����ˡ�\n");
	
	setup();
        carry_object("/d/obj/cloth/cloth")->wear();
        carry_object("/d/obj/weapon/blade/jindao")->wield();
	
	call_out("auto_disapper", AUTO_DEST_TIME);
	call_out("auto_move", AUTO_MOVE_TIME*3/2);
}

int msg()
{
	string *msg=({
		"����Υ���Υ����ʥ˥̣�\n",
		"�ʤˤؤ̤դҤߤ��ʤˣ�\n",
		"�ʤ�㤹���ؤۤ�࣡\n",
		"�ʤؤդˤ�ͤ夽����\n",
		"�������̣�\n",
	});		
	command("say "+msg[random(sizeof(msg))]);
	return 1;
}