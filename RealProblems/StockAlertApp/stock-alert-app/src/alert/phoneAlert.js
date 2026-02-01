require('dotenv').config();
const TelegramBot = require('node-telegram-bot-api');

const token = process.env.TELEGRAM_BOT_TOKEN; // from @BotFather
const chatId = process.env.TELEGRAM_CHAT_ID; // your chat id (use @userinfobot or inspect updates)
let bot = null;

if (token && chatId) {
    bot = new TelegramBot(token, { polling: false });
}

const sendPhoneAlert = async (message) => {
    if (!bot) {
        console.log(`Phone alert (not configured): ${message}`);
        return;
    }
    try {
        await bot.sendMessage(chatId, message);
        console.log('Telegram alert sent');
    } catch (err) {
        console.error('Error sending Telegram alert:', err);
    }
};

module.exports = sendPhoneAlert;

// Temporary placeholder function
// const sendPhoneAlert = (message) => { 
//     console.log(`Phone alert: ${message}`);
// };

// const twilio = require('twilio');
// const accountSid = 'your_account_sid'; // Replace with your Twilio account SID
// const authToken = 'your_auth_token'; // Replace with your Twilio auth token
// const client = new twilio(accountSid, authToken);

// uncomment this later
// const sendPhoneAlert = (message, to) => {
//     client.messages.create({
//         body: message,
//         to: to,  // Text this number
//         from: 'your_twilio_number' // Replace with your Twilio number
//     })
//     .then((message) => console.log(`Alert sent: ${message.sid}`))
//     .catch((error) => console.error('Error sending alert:', error));
// };