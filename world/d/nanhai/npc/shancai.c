
// shancai.c �Ʋ�ͯ��
// By Lestat 2001
inherit NPC;
inherit F_MASTER;
#include "place.h"
int ask_huohun();
//string ask_for_partner();
//string ask_mieyao();
//string ask_cancel();

void create()
{
        set_name("�Ʋ�ͯ��", ({ "shancai tongzi", "shancai", "tongzi" }));
        set("title", "�Ϻ������̴�");   
        set("long", @LONG
�Ϻ�������ǰ���������Ʋ�ͯ�ӡ�
LONG);
        set("gender", "����");
        set("age", 15);
        set("attitude", "peaceful");
        set("rank_info/self", "ƶɮ");
        set("class", "bonze");
    
    set("max_kee", 2000);
        set("max_gin", 600);
           set("max_sen", 2000);
        set("force", 2000);
        set("max_force", 2000);
        set("force_factor", 175);
        set("max_mana", 2000);
        set("mana", 2000);
        set("mana_factor", 155);
        set("combat_exp", 1750000);
		set("daoxing", 1750000);

        set("eff_dx", 150000);
        set("nkgain", 300);

        set_skill("literate", 150);
        set_skill("spells", 150);
        set_skill("buddhism", 150);
        set_skill("unarmed", 150);
        set_skill("jienan-zhi", 150);
        set_skill("dodge", 150);
        set_skill("lotusmove", 150);
        set_skill("parry", 150);
        set_skill("force", 150);
        set_skill("lotusforce", 150);
        set_skill("staff", 150);
        set_skill("lunhui-zhang", 150);
        map_skill("spells", "buddhism");
        map_skill("unarmed", "jienan-zhi");
        map_skill("dodge", "lotusmove");
        map_skill("force", "lotusforce");
        map_skill("parry", "lunhui-zhang");
        map_skill("staff", "lunhui-zhang");


        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                (: cast_spell, "bighammer" :),
                (: cast_spell, "jingang" :)
        }) );
	set("inquiry",([
      		"�캢��"    : (: ask_huohun :),
      			]));
        create_family("�Ϻ�����ɽ", 2, "����");

        setup();
        carry_object("/d/nanhai/obj/sengpao")->wear();
}

void attempt_apprentice(object ob)
{
        if (!((string)ob->query("bonze/class") =="bonze" )) {
                command("say " + RANK_D->query_respect(ob) + "δ����ţ�ˡƶɮ���ܽ��ɡ�\n");
                return;
        }       
        if (((int)ob->query_skill("buddhism", 1) < 70 )) {
                command("say " + RANK_D->query_respect(ob) + "�������ޣ��������𷨡�\n");
                return;
        }
        command("nod");
        command("say �ܺã�ƶɮ�������㣬ϣ������Ŭ�������������\n");

        command("recruit " + ob->query("id") );
        return; 
}

int ask_huohun()
{
	object me = this_player();
	object hong;
	//if( me->query_temp("huohun/zhenshen") )	
	//{
		hong = new("/d/nanhai/npc/honghaier");
		command("say �����Ҿ�����Ҫ�ҵĺ캢����");
		message_vision(HIR"\n$N�����ֳ�һ�ź����Ⱥ�����ʧʱ��$N�Ѿ���ȫ���˸����ӣ�\n"NOR,this_object());
		hong->move(environment(me));
		destruct(this_object());
		return 1;
	//}
	//else
	//	return 0;
}