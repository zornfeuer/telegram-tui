#ifndef CHAT_H
#define CHAT_H

typedef struct {
    char* type;
} ChatType;

typedef struct {
  int can_send_basic_messages;
  int can_send_audios;
  int can_send_documents;
  int can_send_photos;
  int can_send_videos;
  int can_send_video_notes;
  int can_send_voice_notes;
  int can_send_polls;
  int can_send_other_messages;
  int can_add_link_previews;
  int can_change_info;
  int can_invite_users;
  int can_pin_messages;
  int can_create_topics;
} ChatPermissions;

typedef struct {
  int use_default_mute_for;
  int mute_for;
  int use_default_sound;
  int sound_id;
  int use_default_show_preview;
  int show_preview;
  int use_default_mute_stories;
  int mute_stories;
  int use_default_story_sound;
  int story_sound_id;
  int use_default_show_story_sender;
  int show_story_sender;
  int use_default_disable_pinned_message_notifications;
  int disable_pinned_message_notifications;
  int use_default_mention_notifications;
  int disable_mention_notifications;
} NotificationSettings;

typedef struct {
    int id;
    ChatType type;
    char* title;
    int accent_color_id;
    int background_custom_emoji_id;
    int profile_accent_color_id;
    int profile_background_custom_emoji_id;
    ChatPermissions permissions;
    int* postitions; //don't fucking know what it is
    int* chat_lists;
    int has_protected_content;
    int is_translatable;
    int is_marked_as_unread;
    int view_as_topics;
    int has_scheduled_messages;
    int can_be_deleted_only_for_self;
    int can_be_deleted_for_all_users;
    int can_be_reported;
    int default_disable_notifications;
    int unread_count;
    int last_read_inbox_message_id;
    int last_read_outbox_message_id;
    int unread_mention_count;
    int unread_reaction_count;
    NotificationSettings notification_settings;
    int max_reaction_count;
    int message_auto_delete_time;
    char* theme_name;
    int reply_markup_message_id;
    char* client_data;
} Chat;

#endif // CHAT_H
