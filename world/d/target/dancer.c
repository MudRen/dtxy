//captor.c

inherit NPC;
#include <ansi.h>
#include <auto_move.h>
int msg();

void create()
{
	mapping name;
	
	name=NAME_D->random_name("female");
	set_name(name["name"], name["id"]);
	set("title", name["title"]);
	set("age", 20+random(10));
	set("per", 20+random(10));
	set("gender", "Ů��");
	set("long", "�����������ĸ�Ů��\n");
	
        set("combat_exp", 1000+random(1000));
        set("wuxue_exp", 5000+random(5000));
        set_skill("unarmed", 10+random(10));
        set_skill("dodge", 10+random(10));
        set_skill("parry", 10+random(10));
        set("max_kee", 100+random(100));
        set("max_sen", 100+random(100));
        set("max_force", 100+random(100));
        set("force", 30);
        set("force_factor",2);
        set("mana_factor", 2);
        set("max_mana", 50+random(50));
        set("mana", 20);

	set("chat_chance", 20);
	set("chat_msg", ({
		(: random_move :),
		(: msg :),
	}));

	set("move_msg/out", "$N����������������һ������\n");
	set("move_msg/int", "$N������������������������\n");
	set("move_msg/dis", "$N����������������һ������\n");
	
	setup();
        carry_object("/d/obj/cloth/xiuhuaxie")->wear();
        carry_object("/d/obj/cloth/pink_cloth")->wear();
	
	call_out("auto_disapper", AUTO_DEST_TIME);
	call_out("auto_move", AUTO_MOVE_TIME*3/2);
}

int msg()
{
	string *msg=({	
        "$N������ѣ���������������\n",
        "$N�����������������\n",
        "$N�Ღ���ã�����һ����ˮ��\n",
        "$N������������������������\n",
        "$N����һЦ��¶������С���ѡ�\n",
        "$N�����Ღ���ң��������������������\n",
        "$N������������ȸ��ݺ�衣\n",
                });
        message_vision(msg[random(sizeof(msg))] , this_object());
        return 1;
}
