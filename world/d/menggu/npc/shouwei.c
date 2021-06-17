#include <ansi.h>
inherit NPC;

void create()
{
       set_name("����԰����", ({"wangyou shouwei","shouwei", "shou wei", "wei"}));
       set("gender", "����");
       set("age", 50);
       set("per", 10);
       set("max_kee", 5500);
       set("max_sen", 5500);
       set("force", 8888);
       set("max_force", 5500);
       set("force_factor", 60);
       set("max_mana", 5500);
       set("mana", 9999);
       set("mana_factor", 50);
       set("combat_exp", 10000000); 
       set("daoxing",3000000); 
        set_skill("jinghun-zhang", 250);
        set_skill("tonsillit", 100);
        set_skill("gouhunshu", 250);
        set_skill("unarmed", 250);
        set_skill("whip", 250);
        set_skill("sword", 250);
        set_skill("hellfire-whip",250);
        set_skill("zhuihun-sword", 250);
        set_skill("dodge", 120);
        set_skill("ghost-steps", 250);
        set_skill("parry", 250);
        set_skill("spells", 250);
        set_skill("force", 250);
        map_skill("sword", "zhuihun-sword");
        map_skill("parry", "zhuihun-sword");
        map_skill("dodge", "ghost-steps");
        map_skill("unarmed", "jinghun-zhang");
        map_skill("force", "tonsillit");
        map_skill("whip", "hellfire-whip");
        map_skill("spells", "gouhunshu");
        set("family/family_name","���޵ظ�");
        set("nk_gain", 500);
        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: exert_function, "sheqi" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
/*
                (: perform_action, "sword", "duoming" :),
                (: perform_action, "sword", "three" :),     
                (: perform_action, "sword", "yanluo" :), 
                (: perform_action, "unarmed", "zhua" :),                                                
*/
        }) );
        setup();
        carry_object("/d/obj/cloth/mangpao")->wear();
        carry_object("/d/obj/weapon/sword/qinghong")->wield();
        add_temp("apply/armor", 50);
        add_temp("apply/dodge", 50);
}

