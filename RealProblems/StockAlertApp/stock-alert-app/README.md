# Stock Alert App

This is a mini application that scrapes stock values and raises phone alerts when the price exceeds or dips below specified thresholds.

## Project Structure

```
stock-alert-app
├── src
│   ├── app.js            # Entry point of the application
│   ├── scraper
│   │   └── stockScraper.js # Function to scrape stock prices
│   ├── alert
│   │   └── phoneAlert.js  # Function to send phone alerts
│   └── config
│       └── thresholds.js   # Configuration for price thresholds
├── package.json           # NPM configuration file
└── README.md              # Project documentation
```

## Installation

1. Clone the repository:
   ```
   git clone <repository-url>
   cd stock-alert-app
   ```

2. Install the dependencies:
   ```
   npm install
   ```

## Usage

1. Set your desired stock thresholds in `src/config/thresholds.js`:
   ```javascript
   module.exports = {
       upperThreshold: 150, // Set your upper threshold
       lowerThreshold: 100  // Set your lower threshold
   };
   ```

2. Run the application:
   ```
   node src/app.js
   ```

## Alerts

The application will send SMS alerts when the stock price exceeds the upper threshold or dips below the lower threshold. Ensure you have configured the SMS service in `src/alert/phoneAlert.js`.

## Contributing

Feel free to submit issues or pull requests for improvements or bug fixes. 

## License

This project is licensed under the MIT License.