//captor.c

inherit NPC;
#include <ansi.h>
#include <auto_move.h>
int msg();

void create()
{
	mapping name;
	
	name=NAME_D->random_name("male");
	set_name(name["name"], name["id"]);
	set("title", name["title"]);
	set("age", 20+random(30));
	set("per", 15+random(10));
	set("gender", "����");
	set("long", "������������Ѳ�ߵĲ��죬����ò�Ҫȥ�����ǡ�\n");
	
        set("combat_exp", 100000+random(100000));
        set("wuxue_exp", 500000+random(500000));
        set_skill("unarmed", 100+random(100));
        set_skill("dodge", 100+random(100));
        set_skill("parry", 100+random(100));
        set_skill("stick", 100+random(100));
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

	set("move_msg/out", "$N���������۶�ȥ��\n");
	set("move_msg/int", "$N��������ٱ��۹�����\n");
	set("move_msg/dis", "$N���������۶�ȥ��\n");
	
	setup();
        carry_object("/d/obj/cloth/yayifu")->wear();
        carry_object("/d/obj/weapon/stick/shawei")->wield();
	
	call_out("auto_disapper", AUTO_DEST_TIME);
	call_out("auto_move", AUTO_MOVE_TIME*3/2);
}

int msg()
{
	string *msg=({
		"�����ү��·��\n",
		"������������ȥ�ˣ�\n",
		"������Ǹ��ɻ���û�У�\n",
		"�����ӵ�·��������ˣ�\n",
	});		
	command("say "+msg[random(sizeof(msg))]);
	return 1;
}