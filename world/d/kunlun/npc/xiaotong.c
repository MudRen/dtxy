inherit NPC;
void create()
{
        set_name("Сͯ", ({"xiao tong", "tong"}));
        set("gender", "����" );
        set("age", 16);
        set("long", "һ���ɰ���С��ͯ��\n");
        set("class", "shen");
        set("combat_exp", 10000);
  set("daoxing", 20000);

        set("attitude", "peaceful");
        set("title", "С��ͯ");
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);

        set("per", 20);
        set("max_kee", 200);
        setup();
        carry_object("/d/obj/cloth/xianpao")->wear();
}
void init()
{       
        object ob=this_player();
        object me=this_object();

        ::init();

        if ( ((int)ob->query("env/invisibility")  == 0) && ((string)environment(me)->query("short")==" [0;1;33m� [1m� [1m� [1m� [1m� [1m� [1m� [1m� [1m� [1m� [0m") )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        if ( (int)ob->query("combat_exp")>500000 )
                command("say ��λ" + RANK_D->query_respect(ob) + "ʧӭ�ˣ���ӭ���������鶴��\n");
        else if ( (int)ob->query("combat_exp")>100000 )
                command("say ��λ" + RANK_D->query_respect(ob) + "ʧӭ�ˣ�����������ӭ���������鶴��\n");
        else if ( (int)ob->query("combat_exp")>10000 )
                command("say ��λ" + RANK_D->query_respect(ob) + "���������ò裡\n");
        else if ( (int)ob->query("combat_exp")>1000 )
                command("hi " + ob->query("id"));       
        else
                return;
}
