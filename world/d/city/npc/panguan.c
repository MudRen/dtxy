#include <ansi.h>
// Edit By Canoe
// ���ܻ�
inherit NPC;
#define BS "/d/city/prison"  //�ܳͷ�����ұ������ĵص㣬Ϊ�˱���������ô�NPC���ף�������
                             //��˵�໰���͵�����Ӷ��ﵽ�����Ŀ�ģ����ԣ��˵ص�����ڵ����� 
                             //���췿�䣺�������
#define TJ "/d/city/kezhan"  //�����йٰ칫�ص㣬Ϊ�˷�ֹ������ֹͣ��ɥʧ���ܣ��˵ص�����Ǿ�������Ҿ����ĵط������Ĺ㳡�����.
string *msg_d = ({
                      "�����","�����","ɵB","�Ҳ�","����","������˯",
                    "�٣�","��!","fuck","FUCK","Fuck","���","f~u~c~k",
                    "�����̵�","����������","�����","��үү��",
                    "��ƨ","����","�Ź�ƨ","�������ƨ","tmd",
                   "wo cao","fUck","fuCk","fucK","Tmd","tMd",
                    "tmD","Tmmd","tMmd","tmMd","tmmD","Tnnd","tNnd",
                    "tnNd","tnnD","SB","������","������",
                    "�����","��������","������","��������","������","����С��",
                    "Wo kao","wO kao","wo Kao","wo kAo","wo kaO",
                   "Wokao","wOkao","woKao","wokAo","wokaO",
                    "cAo","caO","Kao","kAo","kaO","��������","������ĸ",
                    "�����","�����","sHit","shIt","shiT","����ʦ",
                    "TMD","tmmd","TMMD","tnnd","TNND","wokao",
                    "wo kao","������","������","������","�������","��ƨ��ʦ",
                    "����","��ƨwiz","��wiz","��wiz","����ʦ","������","shit",
                      "SHIT","Shit","wocao","wo cao","ǿ����",
                      
                      });

void punish(object ob,string msg);

void create()
{
    set_name(HIR"�����й�"NOR, ({"pan guan", "panguan", "guan"}));
        set("gender", "����" );
        set("age", 35);
  set("title","������˽");
        set("per", 5);

 set("long", HIR"���˲�֪�������й٣�רΪά����վ������Ϸ�������衣\n"NOR);
        set("combat_exp", 5000000);
        set("attitude", "peaceful");
        set_skill("unarmed", 800);
       set_skill("dodge", 800);
       set_skill("parry", 800);
       set_skill("blade", 800); 
       set_skill("force", 800); 
       set_skill("literate", 800);   
//     set("no_shown", 1); 
       set("max_force", 40000);   
       set("force", 40000);
       set("max_mana", 40000);
       set("mana", 40000);
       set("max_kee", 40000);
       setup();  

//�����Ǳ���ص�Ƶ������MUD��ͬ��
       if( clonep() ) CHANNEL_D->register_relay_channel("rumor");
       if( clonep() ) CHANNEL_D->register_relay_channel("chat");
        if( clonep() ) CHANNEL_D->register_relay_channel("party");
 if( clonep() ) CHANNEL_D->register_relay_channel("qq");
       if( clonep() ) CHANNEL_D->register_relay_channel("es");
       if( clonep() ) CHANNEL_D->register_relay_channel("xyj");
       if( clonep() ) CHANNEL_D->register_relay_channel("sldh");
//   if( clonep() ) CHANNEL_D->register_relay_channel("baby");
}  

void relay_channel(object ob, string channel, string msg) 
 {
          int i;
          if( !userp(ob) || (channel == "sys") ) 
                  return; //npc��ϵͳ��Ϣ���ܴ����� 
         if(wizardp(ob)) return;//wizard��������
          for(i=0; i<sizeof(msg_d); i++) //��������
         {
              if( strsrch(msg, msg_d[i]) >= 0) //����(��Ƶ���Ļ���)
                    {
                     ob->add_temp("maren",1);  
                       if(ob->query_temp("maren")>1||time()-ob->query("last_maren") <60)
                      {
                      ob->delete_temp("maren");
call_out("punish0",0,ob);
                      }
else tell_object(ob,HIW"��ͻȻ����һ��,ԭ���ǲ�С��������!\n�㱻������,С�ı���Ŷ!\n"NOR);
    ob->set("last_maren", time());   
                     return;  
                    }  
          }
  }
void punish0(object ob)
{
         ob->start_busy(30);
command("chat* ���������й�һ��ŭ�ȣ�"+ob->query("name")+"�����ˣ�С����,�������!");
           call_out("punish", 30, ob);
        }

void punish(object ob,string msg)
  {
          object *inv;
          int i;
   if(ob->is_fighting()||ob->is_busy())
    {
    call_out("punish", 1, ob); return; }
         message_vision(HIC"���з���һ�����ӣ�һ�¾���ס$N�Ĳ��ӡ�\n"NOR+CYN"$N�쳤��ͷ����"+
   "�Ű��۵ر������ˡ�\n"NOR, ob);
          ob->move("/d/city/prison");
          ob->set("channel/chat_block",time()+900);
          message_vision(CYN"�����йٿ�Ц��:С����,�����ź�!\n"NOR, ob);
          message_vision(CYN"˵�ţ�����һ�ɣ�$N�����ڵ��ϡ�\n"NOR, ob);
          inv = all_inventory(ob);
          for(i=0; i<sizeof(inv); i++) 
              {
                         destruct(inv[i]);
               }
          ob->be_ghost(1);
          ob->add("gab_word",1);  //��һ��˵�໰ֻ�Ǿ��档
       ob->apply_condition("maren",5+(int)ob->query("gab_word")*5);
          return;
          } 
