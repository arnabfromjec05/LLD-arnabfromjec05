const nodemailer = require('nodemailer');
require('dotenv').config();

// 1. Create a dummy gmail account for sending alerts.
// 2. Enable "Less secure app access" in the gmail account settings or use App Passwords if 2FA is enabled.
// 3. Set the following environment variables in a .env file:
const transporter = nodemailer.createTransport({
    service: 'gmail',
    auth: {
        user: process.env.ALERT_EMAIL_USER,
        pass: process.env.ALERT_EMAIL_PASS,
    },
});

// const sendEmailAlert = async (subject, text) => {
//     const mailOptions = {
//         from: process.env.ALERT_EMAIL_USER,
//         to: process.env.ALERT_EMAIL_TO,
//         subject,
//         text,
//     };

//     try {
//         await transporter.sendMail(mailOptions);
//         console.log('Email alert sent!');
//     } catch (error) {
//         console.error('Error sending email:', error);
//     }
// };

const sendEmailAlert = (subject, text) => {
    console.log(`Email alert - Subject: ${subject}, Text: ${text}`);
};

module.exports = sendEmailAlert;