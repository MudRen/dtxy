inherit NPC;
#include <ansi.h>
void create()
{
        set_name("��ū", ({"julong nu", "long nu","longnu","nu","long"}));
       set("family/family_name", "��������");

        set("long","������������\n");
       set("gender", "����");
       set("age", 30);
        set("title", HIG"��������"NOR);
       set("combat_exp", 1260000);
       set("daoxing", 1500000);
       set("per", 20);
       set("str", 30);
       set("max_kee", 3000);
       set("max_gin", 400);
       set("max_sen", 1500);
       set("force", 3000);
       set("max_force", 1500);
       set("force_factor", 120);
       set("max_mana", 800);
       set("mana", 1600);
       set("mana_factor", 40);
       set("combat_exp", 1200000);
       set("daoxing", 1500000);
       set_skill("huntian-hammer", 200);
        set_skill("hammer", 200);
       set_skill("unarmed", 200);
       set_skill("dodge", 200);
       set_skill("force", 200);
       set_skill("parry", 200);
       set_skill("fork", 200);
       set_skill("spells", 200);
        set_skill("seashentong", 200);
        set_skill("dragonfight", 200);
        set_skill("dragonforce", 200);
        set_skill("fengbo-cha", 200);
        set_skill("dragonstep", 200);
        map_skill("hammer", "huntian-hammer");
        map_skill("spells", "seashentong");
        map_skill("unarmed", "dragonfight");
        map_skill("force", "dragonforce");
        map_skill("fork", "fengbo-cha");
        map_skill("parry", "fengbo-cha");
        map_skill("dodge", "dragonstep");
       set("chat_chance_combat", 50);
       set("chat_msg_combat", ({
                (: cast_spell, "hufa" :),
                (: perform_action, "unarmed", "sheshen" :),
                }) );
        set_temp("apply/armor",50);
        set_temp("apply/damage",25);
        setup();
        carry_object("/d/sea/obj/longpao")->wear();
}

