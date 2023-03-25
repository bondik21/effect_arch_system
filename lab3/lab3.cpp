#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Інтерфейс який дозволяє зберегти та відновити стан об'єкта
class Memento {
public:
    virtual ~Memento() = default;
};

//Клас збереження налаштуваннь користувача
class UserSettings {
public:

	//повідомлення
    void SetNotificationEnabled(bool value) {
        notification_enabled_ = value;
    }

	//звук під час повідомлення
    void SetSoundEnabled(bool value) {
        sound_enabled_ = value;
    }

    bool IsNotificationEnabled() const {
        return notification_enabled_;
    }

    bool IsSoundEnabled() const {
        return sound_enabled_;
    }

    //Зберігаємо поточний стан користувача у патерн знімок
    unique_ptr<Memento> SaveToMemento() const {
        return make_unique<SettingsMemento>(notification_enabled_, sound_enabled_);
    }

    //Відновлюємо стан користувача з патерну
    void RestoreFromMemento(const Memento& memento) {
        const auto& settings_memento = static_cast<const SettingsMemento&>(memento);
        notification_enabled_ = settings_memento.notification_enabled_;
        sound_enabled_ = settings_memento.sound_enabled_;
    }

private:
    //Внутрішній клас збереження стану користувача
    class SettingsMemento : public Memento {
    public:
        SettingsMemento(bool notification_enabled, bool sound_enabled)
            : notification_enabled_{notification_enabled},
              sound_enabled_{sound_enabled} {}

        bool notification_enabled_;
        bool sound_enabled_;
    };

    bool notification_enabled_ = true;
    bool sound_enabled_ = true;
};

//Клас змін налаштуваннь користувачем
class UserSettingsOperation {
public:
    UserSettingsOperation(UserSettings& user_settings)
        : user_settings_{user_settings} {}

    //Зберігаємо поточний стан користувача у патерн
	void SaveUserSettings() {
		memento_ = user_settings_.SaveToMemento();
	}
	
	//Відновлення стану користувача з патерну
	void RestoreUserSettings() {
		user_settings_.RestoreFromMemento(*memento_);
	}
	
	private:
		UserSettings& user_settings_;
		std::unique_ptr<Memento> memento_;
	};

	int main() {
		UserSettings user_settings;
		UserSettingsOperation operation{user_settings};
		
	//Встановлення налаштування користувача
user_settings.SetNotificationEnabled(true);
user_settings.SetSoundEnabled(false);

//Збереження поточного стану користувача
operation.SaveUserSettings();

//Зміна налаштуваннь користувача
user_settings.SetNotificationEnabled(false);
user_settings.SetSoundEnabled(true);

//Відновлення попереднього стану користувача
operation.RestoreUserSettings();

//Перевірка того, що стан користувача відновлено
	cout << "Повідомлення увімкнені: " << user_settings.IsNotificationEnabled() << '\n';
	cout << "Звукове сповіщеня увімкнено: " << user_settings.IsSoundEnabled() << '\n';
return 0;
	}